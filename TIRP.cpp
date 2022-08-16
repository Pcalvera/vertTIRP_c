//

#include "TIRP.h"
TIRP::TIRP() {
    this->ti = vector<TI*>();
    this->r = vector<char>();
    this->first = 0;
    this->max_last = 0;
}

TIRP::TIRP(const shared_ptr<TIRP> &tirp) {
    this->ti = tirp->ti;
    this->first = tirp->first;
    this->max_last = tirp->max_last;
    this->r = tirp->r;
}

TIRP::TIRP(vector<TI*> ti, time_type first, time_type max_last) {
    this->ti = ti;
    this->r = vector<char>();
    this->first = first;
    this->max_last = max_last;
}

TIRP::TIRP(vector<TI*> &ti, time_type first, time_type max_last, vector<char> &r) {
    this->ti = ti;
    this->r = r;
    this->first = first;
    this->max_last = max_last;
}

bool TIRP::operator<(const TIRP &rhs) const {
    if ( this->first < rhs.first)
        return true;
    if ( this->first == rhs.first)
        return this->max_last < rhs.max_last;
    return false;
}

string TIRP::get_rel_as_str() const {
    string s = EMPTY;
    for (char i : this->r)
        s += i;
    return s;
}

time_type TIRP::get_duration() const {
    return this->max_last - this->first;
}

time_type TIRP::get_first() const {
    return this->first;
}

vector<TI*>&  TIRP::get_ti() {
    return this->ti;
}

pair<shared_ptr<TIRP>, unsigned>
TIRP::extend_with(TI* s_ti, eps_type eps, time_type min_gap, time_type max_gap, time_type max_duration,
                  bool mine_last_equal, Allen &allen, Chrono &chrono) const {
    // calc and assign the last relation
    int* rel = allen.calc_rel(this->ti.back(), s_ti, eps, min_gap,max_gap, shared_ptr<PairingStrategy>(nullptr), shared_ptr<vector<string>>(nullptr));
    // the s-extension case
    if ( !mine_last_equal && rel[0] == 'e' )
        return make_pair(nullptr, 1);

    if ( rel[1] < 3 )
        // max gap o min gaps exceded
        return make_pair(nullptr, rel[1]);

    // ini new relation
    vector<char> new_rel = vector<char>(this->r);
    //for ( const char &c : this->r ) new_rel.emplace_back(to_string(c));
    for ( int i = 0 ; i < this->ti.size() ; i++ ) new_rel.emplace_back('\0');

    new_rel.back() = rel[0];

    //chrono.start("extend_with_3");
    // copy if this->ti
    vector<TI*> new_ti = vector<TI*>(ti);
    // append s_ti
    new_ti.emplace_back(s_ti);

    // determine the maximum end time
    time_type new_max_last = s_ti->get_end();
    if ( new_max_last < this->max_last )
        new_max_last = this->max_last;

    // max duration constraint
    if ( (new_max_last-this->first) > max_duration )
        return make_pair(nullptr, 1);

    int size_rel = new_rel.size();
    int size_sym = new_ti.size();

    int r_idx = 1;
    int temp = size_sym - r_idx;
    int first_pos = int(((pow(temp,2)-temp)/2)-1);
    while ( first_pos >= 0 ){
        int second_pos = size_rel - r_idx;
        int pos_to_assign = second_pos - 1;
        TI* existent_node = new_ti[temp-2];
        if ( allen.get_trans() ){
            Relation &possible_rels = allen.get_possible_rels(new_rel[first_pos], new_rel[second_pos] );
            rel = allen.assign_rel(existent_node,s_ti,possible_rels,eps, min_gap, max_gap);
        }
        else {
            rel = allen.calc_rel(existent_node, s_ti, eps, min_gap, max_gap, shared_ptr<PairingStrategy>(nullptr), shared_ptr<vector<string>>(nullptr));
        }

        if ( rel[1] < 3 )
            // max gap or min gaps exceeded
            return make_pair(nullptr, rel[1]);


        //  assigns the relation to the position
        new_rel[pos_to_assign] = rel[0];

        r_idx++;
        temp = size_sym - r_idx;
        first_pos = int(((pow(temp,2) - temp) / 2) - 1);
    }
    return make_pair(std::make_shared<TIRP>(new_ti,new_ti[0]->get_start() ,new_max_last,new_rel),3);
}

time_type TIRP::get_max_last() const {
    return this->max_last;
}

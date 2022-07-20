//
// Created by pauca on 10/04/2022.
//

#include "TIRP.h"
TIRP::TIRP() {
    this->ti = vector<TI>();
    this->r = vector<char>();
    this->first = 0;
    this->max_last = 0;
}
TIRP::TIRP(vector<TI> ti, long long first, long long max_last, vector<char> r) {
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

bool TIRP::operator>(const TIRP &rhs) const {   //TODO comprovar que funcioni correctament
    return rhs < *this;
}

bool TIRP::operator<=(const TIRP &rhs) const {   //TODO comprovar que funcioni correctament
    return !(rhs < *this);
    //if ( this->first < rhs.first)       TODO fa falta posar aquest codi?
    //    return true;
    //if ( this->first == rhs.first)
    //    return this->max_last < rhs.max_last;
    //return false;
}

bool TIRP::operator>=(const TIRP &rhs) const {   //TODO comprovar que funcioni correctament
    return !(*this < rhs);
}

string TIRP::get_rel_as_str() const {   //TODO comprovar que funcioni correctament
    string s = "";
    for (auto i : this->r)
        s += i;
    return s;
}

long long TIRP::get_duration() const {   //TODO comprovar que funcioni correctament
    return this->max_last - this->first;
}

long long TIRP::get_first() const {
    return this->first;
}

vector<TI> TIRP::get_ti() const {
    return this->ti;
}

pair<pair<bool, TIRP>, unsigned>
TIRP::extend_with(const TI &s_ti, float eps, long long int min_gap, long long int max_gap, long long int max_duration,
                  bool mine_last_equal, const Allen &allen) const {
    TIRP nullTirp;
    // calc and assign the last relation
    pair<char,int> rel = allen.calc_rel(this->ti.back(), s_ti, eps, min_gap,max_gap ); //TODO

    // the s-extension case
    if ( !mine_last_equal && rel.first == 'e' )
        return make_pair(make_pair(false,nullTirp),1);

    if ( rel.second < 3 )
        // max gap o min gaps exceded
        return make_pair(make_pair(false,nullTirp),rel.second);

    // ini new relation
    vector<char> new_rel = vector<char>(this->r);
    //for ( const char &c : this->r ) new_rel.emplace_back(to_string(c));
    for ( int i = 0 ; i < this->ti.size() ; i++ ) new_rel.emplace_back('\0');

    new_rel.back() = rel.first;

    // copy if this->ti
    vector<TI> new_ti = vector<TI>(ti);
    // append s_ti
    new_ti.emplace_back(s_ti);

    // determine the maximum end time
    long long new_max_last = s_ti.get_end();
    if ( new_max_last < this->max_last )
        new_max_last = this->max_last;

    // max duration constraint
    if ( (new_max_last-this->first) > max_duration )
        return make_pair(make_pair(false,nullTirp),1);

    int size_rel = new_rel.size();
    int size_sym = new_ti.size();

    int r_idx = 1;
    int temp = size_sym - r_idx;
    int first_pos = int(((pow(temp,2)-temp)/2)-1);
    while ( first_pos >= 0 ){
        int second_pos = size_rel - r_idx;
        int pos_to_assign = second_pos - 1;
        TI existent_node = new_ti[temp-2];
        if ( allen.get_trans() ){
            Relation possible_rels = allen.get_possible_rels(new_rel[first_pos], new_rel[second_pos] );
            rel = allen.assign_rel(existent_node,s_ti,possible_rels,eps, min_gap, max_gap);
        }
        else
            // calc and assign the last relation
            rel = allen.calc_rel(existent_node, s_ti, eps, min_gap, max_gap );

        if ( rel.second < 3 )
            // max gap or min gaps exceeded
            return make_pair(make_pair(false,nullTirp),rel.second);

        //  assigns the relation to the position
        new_rel[pos_to_assign] = rel.first;

        r_idx++;
        temp = size_sym - r_idx;
        first_pos = int(((pow(temp,2) - temp) / 2) - 1);
    }

    return make_pair(make_pair(true,TIRP(new_ti,new_ti[0].get_start(),new_max_last,new_rel)),3);
}

long long TIRP::get_max_last() const {
    return this->max_last;
}

//TODO funcio copy???

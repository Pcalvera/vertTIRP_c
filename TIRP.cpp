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
TIRP::TIRP(vector<TI> ti, long long first, long long max_last, vector<char> r) { //TODO comprovar que funcioni correctament
    this->ti = ti;
    this->r = r;
    this->first = first;
    this->max_last = max_last;
}

bool TIRP::operator<(const TIRP &rhs) const {   //TODO comprovar que funcioni correctament
    if ( this->first < rhs.first)
        return true;
    if ( this->first == rhs.first)
        return this->max_last < rhs.max_last;
    return false;
}

bool TIRP::operator>(const TIRP &rhs) const {    //TODO comprovar que funcioni correctament
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

pair<pair<bool, TIRP&>, unsigned>
TIRP::extend_with(const TI &s_ti, float eps, long long int min_gap, long long int max_gap, long long int max_duration,
                  bool mine_last_equal, const Allen &allen) const {
    TIRP nullRef;
    // calc and assign the last relation
    pair<char,int> rel = allen.calc_rel(this->ti.back(), s_ti, eps, min_gap,max_gap );

    // the s-extension case
    if ( !mine_last_equal && rel.first == 'e' )
        return make_pair<pair<bool, TIRP&>, unsigned>(make_pair<bool, TIRP&>(false,nullRef),1);

    if ( rel.second < 3 )
        // max gap o min gaps exceded
        return make_pair<pair<bool, TIRP&>, unsigned>(make_pair<bool, TIRP&>(false,nullRef),rel.second);

    // ini new relation
    vector<char> new_rel = vector<char>(this->r);
    //for ( const char &c : this->r ) new_rel.emplace_back(to_string(c));
    for ( int i = 0 ; i < this->ti.size() ; i++ ) new_rel.emplace_back('\0');

    new_rel.back() = rel.first;

    // copy if this->ti
    vector<TI> new_ti = vector<TI>(ti);  //TODO no estic segur si es fa copia dels objectes TI
    // append s_ti
    new_ti.emplace_back(s_ti);

    // determine the maximum end time
    long long new_max_last = s_ti.get_end();
    if ( new_max_last < this->max_last )
        new_max_last = this->max_last;

    // max duration constraint
    if ( new_max_last-this-first > max_duration )
        return make_pair<pair<bool, TIRP&>, unsigned>(make_pair<bool, TIRP&>(false,nullRef),1);

    unsigned size_rel = new_rel.size();
    unsigned size_sym = new_ti.size();

    unsigned r_idx = 1;
    int temp = (int)size_sym - (int)r_idx;
    int first_pos = int(((pow(temp,2))/2)-1);
    while ( first_pos >= 0 ){
        int second_pos = (int)size_rel - (int)r_idx;
        int pos_to_assign = second_pos - 1;
        TI existent_node = new_ti[temp-2];
        if ( allen.get_trans() ){
            Relation possible_rels = allen.get_possible_rels(new_rel[first_pos], new_rel[second_pos] );
            rel = allen.assign_rel();
        }
    }

    return make_pair<pair<bool, TIRP&>, unsigned>(make_pair<bool, TIRP&>(true,TIRP(new_ti,new_ti[0].get_start(),new_max_last,new_rel)),3);
}

long long TIRP::get_max_last() const {
    return this->max_last;
}


//pair<bool, pair<TIRP, unsigned>>
//TIRP::extend_with(TI s_ti, float eps, long long int min_gap, long long int max_gap, long long int max_duration,
//                  bool mine_last_equal, Allen &allen) {
//    //TODO
//}

//TODO funcio copy???

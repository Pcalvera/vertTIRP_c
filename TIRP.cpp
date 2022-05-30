//
// Created by pauca on 10/04/2022.
//

#include "TIRP.h"

TIRP::TIRP(vector<TI> ti, long long first, long long max_last, list<char> r) { //TODO comprovar que funcioni correctament
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
    for (auto i : r)
        s += i;
    return s;
}

long long TIRP::get_duration() const {   //TODO comprovar que funcioni correctament
    return this->max_last - this->first;
}

//pair<bool, pair<TIRP, unsigned>>
//TIRP::extend_with(TI s_ti, float eps, long long int min_gap, long long int max_gap, long long int max_duration,
//                  bool mine_last_equal, Allen &allen) {
//    //TODO
//}

//TODO funcio copy???

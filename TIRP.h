//
// Created by pauca on 10/04/2022.
//

#ifndef VERTTIRP_C_TIRP_H
#define VERTTIRP_C_TIRP_H
#include <iostream>
#include <memory>
#include <cmath>
#include "TI.h"
#include "vector"
#include "list"
#include "Allen.h"
#include "Chrono.h"

using namespace std;

class TIRP {
public:
    TIRP();
    TIRP(vector<shared_ptr<TI>> ti, time_type first, time_type max_last);
    TIRP(vector<shared_ptr<TI>> &ti, time_type first, time_type max_last, vector<char> &r);
    bool operator<(const TIRP &rhs) const;
    bool operator>(const TIRP &rhs) const;
    bool operator<=(const TIRP &rhs) const;
    bool operator>=(const TIRP &rhs) const;
    string get_rel_as_str()const;
    time_type get_duration()const;
    time_type get_first()const;
    vector<shared_ptr<TI>>& get_ti();
    time_type get_max_last()const;
    pair<pair<bool,TIRP>,unsigned> extend_with(const shared_ptr<TI> &s_ti, eps_type eps, time_type min_gap, time_type max_gap, time_type max_duration, bool mine_last_equal, const Allen &allen, Chrono &chrono)const;


private:
    vector<shared_ptr<TI>> ti;
    time_type first;
    time_type max_last;
    vector<char> r;
};


#endif //VERTTIRP_C_TIRP_H

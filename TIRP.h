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
    TIRP(const shared_ptr<TIRP> &tirp);
    TIRP(vector<TI*> ti, time_type first, time_type max_last);
    TIRP(vector<TI*> &ti, time_type first, time_type max_last, vector<char> &r);
    bool operator<(const TIRP &rhs) const;
    string get_rel_as_str()const;
    time_type get_duration()const;
    time_type get_first()const;
    vector<TI*>& get_ti();
    time_type get_max_last()const;
    pair<shared_ptr<TIRP>,unsigned> extend_with(TI* s_ti, eps_type eps, time_type min_gap, time_type max_gap, time_type max_duration, bool mine_last_equal, Allen &allen)const;


private:
    vector<TI*> ti;
    time_type first;
    time_type max_last;
    vector<char> r;
};


#endif //VERTTIRP_C_TIRP_H

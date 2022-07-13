//
// Created by pauca on 10/04/2022.
//

#ifndef VERTTIRP_C_TIRP_H
#define VERTTIRP_C_TIRP_H
#include <iostream>
#include <cmath>
#include "TI.h"
#include "vector"
#include "list"
#include "Allen.h"

using namespace std;

class TIRP {
public:
    TIRP();
    TIRP(vector<TI> ti, long long first, long long max_last, vector<char> r = vector<char>() );
    bool operator<(const TIRP &rhs) const;
    bool operator>(const TIRP &rhs) const;
    bool operator<=(const TIRP &rhs) const;
    bool operator>=(const TIRP &rhs) const;
    string get_rel_as_str()const;
    long long get_duration()const;
    long long get_first()const;
    vector<TI> get_ti()const;
    long long get_max_last()const;
    pair<pair<bool,TIRP>,unsigned> extend_with(const TI &s_ti, float eps, long long min_gap, long long max_gap, long long max_duration, bool mine_last_equal,const Allen &allen)const;


private:
    vector<TI> ti;
    long long first;
    long long max_last;
    vector<char> r;
};


#endif //VERTTIRP_C_TIRP_H

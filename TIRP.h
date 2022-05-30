//
// Created by pauca on 10/04/2022.
//

#ifndef VERTTIRP_C_TIRP_H
#define VERTTIRP_C_TIRP_H
#include <iostream>
#include "TI.h"
#include "vector"
#include "list"
#include "Allen.h"

using namespace std;

class TIRP {
public:
    TIRP(vector<TI> ti, long long first, long long max_last, list<char> r = list<char>() );
    bool operator<(const TIRP &rhs) const;
    bool operator>(const TIRP &rhs) const;
    bool operator<=(const TIRP &rhs) const;
    bool operator>=(const TIRP &rhs) const;
    string get_rel_as_str()const;
    long long get_duration()const;
    //pair<bool,pair<TIRP,unsigned>> extend_with(TI s_ti, float eps, long long min_gap, long long max_gap, long long max_duration, bool mine_last_equal, Allen &allen);


private:
    vector<TI> ti;
    long long first;
    long long max_last;
    list<char> r;
};


#endif //VERTTIRP_C_TIRP_H

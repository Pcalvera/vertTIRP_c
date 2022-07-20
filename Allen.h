//
// Created by pauca on 30/03/2022.
//

#ifndef VERTTIRP_C_ALLEN_H
#define VERTTIRP_C_ALLEN_H
#include <iostream>
#include "PairingStrategy.h"
#include "Allen_relationsEPS.h"

using namespace std;

class Allen {
public:
    Allen();
    Allen(bool dummy_calc, bool trans = true, eps_type eps = 0, string calc_sort="bselfmoc" );
    string sort_rels(string reducted_group);
    pair<char,int> calc_rel(const TI &a, const TI &b, eps_type eps, long long min_gap, long long max_gap, PairingStrategy rels_arr = PairingStrategy(), vector<string> gr_arr = vector<string>() )const;//TODO hauria de passar per ref
    pair<char,int> assign_rel(const TI &a, const TI &b, const Relation &possible_rels, eps_type eps, long long min_gap, long long max_gap )const;
    Relation get_possible_rels(char a, char b)const;
    bool get_trans()const;
private:
    string calc_sort;
    bool dummy_calc;
    bool trans;
    eps_type eps;

    //For non dummy
    PairingStrategy rels_arr;
    vector<string> gr_arr;
    map<string,Relation> sorted_trans_table;
};


#endif //VERTTIRP_C_ALLEN_H
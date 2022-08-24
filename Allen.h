//
// Created by pauca on 30/03/2022.
//

#ifndef VERTTIRP_C_ALLEN_H
#define VERTTIRP_C_ALLEN_H
#include <iostream>
#include <memory>
#include "PairingStrategy.h"
#include "AllenRelationsEPS.h"

using namespace std;

class Allen {
public:
    Allen();
    Allen(bool dummy_calc, bool trans = true, eps_type eps = 0, string calc_sort="bselfmoc" );
    string sort_rels(string reducted_group);
    int* calc_rel(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap, shared_ptr<PairingStrategy> rels_arr, shared_ptr<vector<std::string>> gr_arr)const;
    int* assign_rel(const TI* a, const TI* b, Relation &possible_rels, eps_type eps, time_type min_gap, time_type max_gap)const;
    Relation& get_possible_rels(char a, char b);
    bool get_trans()const;
private:
    string calc_sort;
    bool dummy_calc;
    bool trans;
    eps_type eps;

    //For non dummy
    shared_ptr<PairingStrategy> rels_arr;
    shared_ptr<vector<string>> gr_arr;
    map<string,Relation> sorted_trans_table;
};


#endif //VERTTIRP_C_ALLEN_H
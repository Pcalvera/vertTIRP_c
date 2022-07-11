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
    Allen(bool dummy_calc, bool trans = true, float eps = 0, string calc_sort="bselfmoc", Allen_relationsEPS supClass = Allen_relationsEPS() );  //TODO passar supClass per ref?
    string sort_rels(string reducted_group);
    pair<char,int> calc_rel(TI &a, TI &b, float eps, long long min_gap, long long max_gap, PairingStrategy rels_arr = PairingStrategy(), list<string> gr_arr = list<string>() )const;   //TODO passar per ref?
    Relation get_possible_rels(char a, char b)const;
    pair<char,int> assign_rel(TI a, TI b, Relation &possible_rels, float eps, long long min_gap, long long max_gap )const;
    bool get_trans()const;
private:
    string calc_sort;
    bool dummy_calc;
    bool trans;
    float eps;

    Allen_relationsEPS supClass;
    //For non dummy
    PairingStrategy rels_arr;
    list<string> gr_arr;
    map<string,Relation> sorted_trans_table;
};


#endif //VERTTIRP_C_ALLEN_H

//TODO es pot borrar aquest .h (la definicio de la classe esta a Allen_relationsEPS)
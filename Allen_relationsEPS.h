//
// Created by pauca on 04/05/2022.
//

#ifndef VERTTIRP_C_ALLEN_RELATIONSEPS_H
#define VERTTIRP_C_ALLEN_RELATIONSEPS_H
#include <iostream>
#include <cstdlib>
#include "map"
#include "list"
#include "TI.h"
#include "PairingStrategy.h"
#include "Relation.h"

using namespace std;

const long long MAXGAP = 3155695200;
const string NONE = "N";

class Allen_relationsEPS {
public:
    Allen_relationsEPS();
    static pair<PairingStrategy,list<string>> get_pairing_strategy(string str_rels);

    // Trans table based on Mantaining Knowledge about Temporal Intervals
    // by James F.Allen
    map<string,string> trans_table_0;
    //Trans table based of the vertTIRP article
    map<string,string> trans_table;

    //TODO mapes amb funcions
private:

    static void update_added(map<char,bool> &added,char c, bool b);

    //---------------------------------------------- AUX FUNC ----------------------------------------------------------
    static pair<string,int> before_ind(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static pair<string,int> meets_ind(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static pair<string,int> overlaps_ind(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static pair<string,int> contains_ind(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static pair<string,int> finish_by_ind(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static pair<string,int> equal_ind(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static pair<string,int> starts_ind(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static pair<string,int> left_contains_ind(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static bool sel_cond(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static bool cfmo_cond(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static bool mo_cond(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static bool true_cond(TI a, TI b, float eps, long long min_gap, long long max_gap);
    //---------------------------------------------- END AUX FUNC ------------------------------------------------------

    //---------------------------------------------- DUMMY AUX FUNC ----------------------------------------------------
    static pair<string,int> before(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static pair<string,int> meets(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static pair<string,int> overlaps(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static pair<string,int> contains(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static pair<string,int> finish_by(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static pair<string,int> equal(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static pair<string,int> starts(TI a, TI b, float eps, long long min_gap, long long max_gap);
    static pair<string,int> left_contains(TI a, TI b, float eps, long long min_gap, long long max_gap);
    //---------------------------------------------- END DUMMY AUX FUNC ------------------------------------------------
};


#endif //VERTTIRP_C_ALLEN_RELATIONSEPS_H

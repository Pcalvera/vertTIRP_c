//
// Created by pauca on 04/05/2022.
//

#ifndef VERTTIRP_C_ALLEN_RELATIONSEPS_H
#define VERTTIRP_C_ALLEN_RELATIONSEPS_H
#include <iostream>
#include <cstdlib>
#include <functional>
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
    static pair<PairingStrategy,vector<string>> get_pairing_strategy(string str_rels);

    // Trans table based on Mantaining Knowledge about Temporal Intervals
    // by James F.Allen
    map<string,string> trans_table_0;
    //Trans table based of the vertTIRP article
    map<string,string> trans_table;

    //TODO potser hi ha maneres mes eficients d'implementar-ho
    static map<char,function<pair<char,int>(const TI&,const TI&,float, long long, long long)>> ind_func_dict;
    static map<string,function<bool(const TI&,const TI&,float, long long, long long)>> cond_dict;

    static map<char,function<pair<char,int>(const TI&,const TI&,float, long long, long long)>> rel_func_dict;
    private:

    static void update_added(map<char,bool> &added,char c, bool b);

    //---------------------------------------------- AUX FUNC ----------------------------------------------------------
    static pair<char,int> before_ind(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static pair<char,int> meets_ind(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static pair<char,int> overlaps_ind(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static pair<char,int> contains_ind(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static pair<char,int> finish_by_ind(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static pair<char,int> equal_ind(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static pair<char,int> starts_ind(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static pair<char,int> left_contains_ind(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static bool sel_cond(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static bool cfmo_cond(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static bool mo_cond(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static bool true_cond(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    //---------------------------------------------- END AUX FUNC ------------------------------------------------------

    //---------------------------------------------- DUMMY AUX FUNC ----------------------------------------------------
    static pair<char,int> before(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static pair<char,int> meets(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static pair<char,int> overlaps(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static pair<char,int> contains(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static pair<char,int> finish_by(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static pair<char,int> equal(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static pair<char,int> starts(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    static pair<char,int> left_contains(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap);
    //---------------------------------------------- END DUMMY AUX FUNC ------------------------------------------------
};

//TODO hi han funcions que no necessiten el min_gap i max_gap
#endif //VERTTIRP_C_ALLEN_RELATIONSEPS_H


//
// Created by pauca on 04/05/2022.
//

#ifndef VERTTIRP_C_ALLEN_RELATIONSEPS_H
#define VERTTIRP_C_ALLEN_RELATIONSEPS_H
#include <iostream>
#include <cstdlib>
#include <functional>
#include <memory>
#include "map"
#include "list"
#include "Global.cpp"
#include "TI.h"
#include "PairingStrategy.h"
#include "Relation.h"

using namespace std;

static int rel_11[2] = {'1',1};
static int rel_22[2] = {'2',2};
static int rel_b3[2] = {'b',3};
static int rel_m3[2] = {'m',3};
static int rel_o3[2] = {'0',3};
static int rel_c3[2] = {'c',3};
static int rel_f3[2] = {'f',3};
static int rel_e3[2] = {'e',3};
static int rel_s3[2] = {'s',3};
static int rel_l3[2] = {'l',3};
static int rel_none2[2] = {'\0',2};
static int rel_noneMinus2[2] = {'\0',-2};

class Allen_relationsEPS {
public:


    static pair<PairingStrategy,vector<string>> get_pairing_strategy(string str_rels);

    // Trans table based on Mantaining Knowledge about Temporal Intervals
    // by James F.Allen
    static map<string,string> trans_table_0;
    //Trans table based of the vertTIRP article
    static map<string,string> trans_table;

    //TODO potser hi ha maneres mes eficients d'implementar-ho
    static map<char,function<int*(const shared_ptr<TI>&, const shared_ptr<TI>&, eps_type, time_type, time_type)>> ind_func_dict;
    static map<string,function<bool(const shared_ptr<TI>&, const shared_ptr<TI>&, eps_type, time_type, time_type)>> cond_dict;

    static map<char,function<int*(const shared_ptr<TI>&, const shared_ptr<TI>&, eps_type, time_type, time_type)>> rel_func_dict;


    private:

    static void update_added(map<char,bool> &added,char c, bool b);

    //---------------------------------------------- AUX FUNC ----------------------------------------------------------
    static int* before_ind(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static int* meets_ind(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static int* overlaps_ind(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static int* contains_ind(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static int* finish_by_ind(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static int* equal_ind(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static int* starts_ind(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static int* left_contains_ind(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static bool sel_cond(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static bool cfmo_cond(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static bool mo_cond(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static bool true_cond(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    //---------------------------------------------- END AUX FUNC ------------------------------------------------------

    //---------------------------------------------- DUMMY AUX FUNC ----------------------------------------------------
    static int*  before(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static int*  meets(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static int*  overlaps(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static int*  contains(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static int*  finish_by(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static int*  equal(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static int*  starts(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    static int*  left_contains(const shared_ptr<TI> &a, const shared_ptr<TI> &b, eps_type eps, time_type min_gap, time_type max_gap);
    //---------------------------------------------- END DUMMY AUX FUNC ------------------------------------------------
};

//TODO hi han funcions que no necessiten el min_gap i max_gap
#endif //VERTTIRP_C_ALLEN_RELATIONSEPS_H

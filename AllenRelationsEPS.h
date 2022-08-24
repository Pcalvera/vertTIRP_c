
//
// Created by pauca on 04/05/2022.
//

#ifndef VERTTIRP_C_ALLENRELATIONSEPS_H
#define VERTTIRP_C_ALLENRELATIONSEPS_H
#include <iostream>
#include <cstdlib>
#include <functional>
#include <memory>
#include <cmath>
#include "unordered_map"
#include "Utils.h"
#include "Global.h"
#include "TI.h"
#include "PairingStrategy.h"
#include "Relation.h"

using namespace std;

static int rel_11[2] = {'1',1};
static int rel_22[2] = {'2',2};
static int rel_b3[2] = {'b',3};
static int rel_m3[2] = {'m',3};
static int rel_o3[2] = {'o',3};
static int rel_c3[2] = {'c',3};
static int rel_f3[2] = {'f',3};
static int rel_e3[2] = {'e',3};
static int rel_s3[2] = {'s',3};
static int rel_l3[2] = {'l',3};
static int rel_none2[2] = {'\0',2};
static int rel_noneMinus2[2] = {'\0',-2};

class AllenRelationsEPS {
public:


    static pair< shared_ptr<PairingStrategy>,shared_ptr<vector<string>> > get_pairing_strategy(string str_rels);

    // Trans table based on Mantaining Knowledge about Temporal Intervals
    // by James F.Allen
    static unordered_map<string,Relation> trans_table_0;
    //Trans table based of the vertTIRP article
    static unordered_map<string,Relation> trans_table;
    static unordered_map<char,int*> predefined_rels;

    static unordered_map<char,function<int*(const TI*, const TI*, eps_type, time_type, time_type)>> ind_func_dict;
    static unordered_map<string,function<bool(const TI*, const TI*, eps_type, time_type, time_type)>> cond_dict;

    static unordered_map<char,function<int*(const TI*, const TI*, eps_type, time_type, time_type)>> rel_func_dict;


    private:

    static void update_added(map<char,bool> &added,char c, bool b);
    //---------------------------------------------- AUX FUNC ----------------------------------------------------------
    static int* before_ind(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static int* meets_ind(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static int* overlaps_ind(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static int* contains_ind(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static int* finish_by_ind(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static int* equal_ind(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static int* starts_ind(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static int* left_contains_ind(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static bool sel_cond(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static bool cfmo_cond(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static bool mo_cond(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static bool true_cond(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    //---------------------------------------------- END AUX FUNC ------------------------------------------------------

    //---------------------------------------------- DUMMY AUX FUNC ----------------------------------------------------
    static int*  before(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static int*  meets(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static int*  overlaps(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static int*  contains(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static int*  finish_by(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static int*  equal(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static int*  starts(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    static int*  left_contains(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap);
    //---------------------------------------------- END DUMMY AUX FUNC ------------------------------------------------
};
#endif //VERTTIRP_C_ALLENRELATIONSEPS_H

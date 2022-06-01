/*
author: Pau Calvera
email: paucalvera@gmail.com

This file form part of the implementation of the vertTIRP algorithm described in the article:

Natalia Mordvanyuk, Beatriz López, Albert Bifet,
        vertTIRP: Robust and efficient vertical frequent time interval-related pattern mining,
Expert Systems with Applications,
        Volume 168,
2021,
114276,
ISSN 0957-4174,
https://doi.org/10.1016/j.eswa.2020.114276.
(https://www.sciencedirect.com/science/article/pii/S0957417420309842)
Abstract: Time-interval-related pattern (TIRP) mining algorithms find patterns such as “A starts B” or “A overlaps B”. The discovery of TIRPs is computationally highly demanding. In this work, we introduce a new efficient algorithm for mining TIRPs, called vertTIRP which combines an efficient representation of these patterns, using their temporal transitivity properties to manage them, with a pairing strategy that sorts the temporal relations to be tested, in order to speed up the mining process. Moreover, this work presents a robust definition of the temporal relations that eliminates the ambiguities with other relations when taking into account the uncertainty in the start and end time of the events (epsilon-based approach), and includes two constraints that enable the user to better express the types of TIRPs to be learnt. An experimental evaluation of the method was performed with both synthetic and real datasets, and the results show that vertTIRP requires significantly less computation time than other state-of-the-art algorithms, and is an effective approach.
Keywords: Time Interval Related Patterns; Temporal data mining; Sequential pattern mining; Temporal relations
*/

#ifndef VERTTIRP_C_VERTTIRP_H
#define VERTTIRP_C_VERTTIRP_H
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include <list>
#include <map>
#include "Allen.h"
#include "TI.h"
#include "VertTirpSidList.h"
#include "VertTirpNode.h"

using namespace std;

class VertTIRP {
public:
    VertTIRP(int time_mode,string out_file,float min_sup_rel,float eps,int min_gap,long long max_gap,int min_duration,long long max_duration,bool dummy_calc,string ps,bool trans, int min_confidence = -1,int max_length=-1,int min_length=1);
    int mine_patterns(list<list<TI>> const &list_of_ti_seqs, list<string> const &list_of_seqs, bool avoid_same_var_states = true);
    void print_patterns(bool dfs);
private:
    string out_file;  // output file
    map<string,int> events_per_sequence;   // necessary for relative horizontal support TODO map?
    float min_sup_rel;  // relative minimum vertical support
    int min_confidence; //TODO int?
    int min_gap;  // minimum gap in seconds that is the gap between before consecutive elements
    long long max_gap;  // maximum gap in seconds that is the gap between before consecutive elements
    int min_duration; // each event interval should have a duration of at least min_duration seconds
    long long max_duration; // each tirp should have a duration of at most min_duration seconds
    int max_length;  // maximum pattern length
    int min_length;  // minimum pattern length
    float eps;  // karma lego epsilon in nanoseconds
    int tirp_count; //TODO int?
    float min_sup;  // absolute support //TODO int?
    vector<string> f1;  // holds frequent 1-size items //TODO tipus?
    map<string,VertTirpSidList> vertical_db;  // holds database represented vertically //TODO map?
    VertTirpNode tree;  // we will save the patterns in a tree structure  //TODO estructura arbre
    int time_mode;  //  1- timestamp mode, 2- datetime mode 3- number mode(e.g. number of frame)

    Allen allen;

    bool same_variable(string s1,string s2, bool avoid_same_var_states = true);
    void dfs_pruning(char pat_sidlist, vector<char> &f_l, VertTirpNode father, bool avoid_same_var_states = true );
    void to_vertical(list<list<TI>> const &list_of_ti_seqs, list<string> const &list_of_seqs);
};


#endif //VERTTIRP_C_VERTTIRP_H

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
#include <algorithm>
#include <vector>
#include <map>
#include "TI.h"
#include "VertTirpNode.h"

using namespace std;

class VertTIRP {
public:
    VertTIRP(string &out_file, support_type min_sup_rel, eps_type eps, time_type min_gap, time_type max_gap, int min_duration, time_type max_duration, bool dummy_calc, string &ps, bool trans, float min_confidence = -1, int max_length=-1, int min_length=1);
    int mine_patterns(vector<LinkedList> &list_of_ti_seqs, vector<string> const &list_of_seqs, bool avoid_same_var_states = true);
    void print_patterns(bool dfs);
private:
    Allen allen;
    map<string,unsigned> events_per_sequence;   // necessary for relative horizontal support
    map<string,VertTirpSidList> vertical_db;  // holds database represented vertically
    vector<string> f1;  // holds frequent 1-size items
    VertTirpNode tree;  // we will save the patterns in a tree structure

    string out_file;  // output file
    support_type min_sup_rel;  // relative minimum vertical support
    float min_confidence;
    int min_gap;  // minimum gap in seconds that is the gap between before consecutive elements
    time_type max_gap;  // maximum gap in seconds that is the gap between before consecutive elements
    time_type min_duration; // each event interval should have a duration of at least min_duration seconds
    time_type max_duration; // each tirp should have a duration of at most min_duration seconds
    int max_length;  // maximum pattern length
    int min_length;  // minimum pattern length
    eps_type eps;  // karma lego epsilon in nanoseconds
    int tirp_count;
    support_type min_sup;  // absolute support
    int time_mode;  //  1- timestamp mode, 2- datetime mode 3- number mode(e.g. number of frame)

    bool same_variable(string s1,string s2, bool avoid_same_var_states = true);
    void dfs_pruning(VertTirpSidList &pat_sidlist, vector<string> &f_l, VertTirpNode &node,VertTirpNode &father,int level, bool avoid_same_var_states = true );
    void to_vertical(vector<LinkedList> &list_of_ti_seqs, vector<string> const &list_of_seqs);
};


#endif //VERTTIRP_C_VERTTIRP_H

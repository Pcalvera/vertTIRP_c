#include <iostream>
#include "VertTIRP.h"
#include "TI.h"
#include "Global.h"
#include "PairingStrategy.h"
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



support_type ver_sup = 0.01;  // vertical support TODO float o dobule
support_type hor_sup = 0;  // horizontal support
eps_type eps = 0;  // epsilon value in seconds, that allows uncertainty and avoids crisp borders in relations
bool dummy = true;  // whether to execute relations without a pairing strategies
bool trans = false;  // whether to use transitivity properties when assign a relation
//string result_file_name = "my_result_file.csv";  // an output file
string result_file_name = "my_result_file.csv";  // an output file
string filepath = R"(D:\COLE\TFG\toy.csv)";  // a path to time interval data. Any valid string path is acceptable.
//string filepath = "/mnt/d/COLE/TFG/toy.csv";  // a path to time interval data. Any valid string path is acceptable.
char sep = ';';  // delimiter to use with the scv file
string sid_column = "sid";   // sequence column name
string date_column_name_start = "start_time";  // start time column name
string date_column_name_end = "end_time";  // end time column name
string date_format = "%m/%d/%Y %H:%M";  // the format of the date, e.g. "3/1/2003 10:10" will be "%m/%d/%Y %H:%M"
vector<string> value_column_name = vector<string>({"value"});  // the interesting attributes to be used in TIRPs discovering  //TODO taula?


bool avoid_same_var_states = false;
time_type ming = 0;  // minimum gap in seconds that is the gap between before consecutive elements
time_type maxg = 3155695200;  // maximum gap in seconds that is the gap between before consecutive elements
time_type mind = 0;  // each event interval should have a duration of at least min_duration seconds
time_type maxd = 3155695200;   // each tirp should have a duration of at most min_duration seconds
string ps = "mocfbes";

int main () {
    ReadTi filePatterns = utils_tiRead(filepath, sep, sid_column, date_column_name_start, date_column_name_end,
                                       date_format, value_column_name, true);
    vector<vector<TI>> list_of_ti_users = filePatterns.list_of_ti_users;
    vector<string> list_of_users = filePatterns.list_of_users;
    int ti_count = filePatterns.ti_count;

    VertTIRP co = VertTIRP(result_file_name,ver_sup,eps,ming,maxg,mind,maxd,dummy,ps,trans);
    int tirp_count = co.mine_patterns(list_of_ti_users,list_of_users,avoid_same_var_states);
    co.print_patterns(false);
    cout << "Algorithm finished" << endl;
    return 0;
}
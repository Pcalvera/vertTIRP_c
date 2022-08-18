#include <iostream>
#include <omp.h>
#include "VertTIRP.h"
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


bool timemode_number = true;
support_type ver_sup = 0.9;  // vertical support
support_type hor_sup = 0;  // horizontal support
eps_type eps = 0;  // epsilon value in seconds, that allows uncertainty and avoids crisp borders in relations
bool dummy = true;  // whether to execute relations without a pairing strategies
bool trans = true;  // whether to use transitivity properties when assign a relation
//string result_file_name = "my_result_file.csv";  // an output file
//string filepath = "/mnt/d/COLE/TFG/toy.csv";  // a path to time interval data. Any valid string path is acceptable.
char sep = ';';  // delimiter to use with the scv file
/* //TOY.csv
string result_file_name = "toy_result_file.csv";  // an output file
string filepath = R"(../toy.csv)";  // a path to time interval data. Any valid string path is acceptable.
string sid_column = "sid";   // sequence column name
string date_column_name_start = "start_time";  // start time column name
string date_column_name_end = "end_time";  // end time column name
string date_format = "%m/%d/%Y %H:%M";  // the format of the date, e.g. "3/1/2003 10:10" will be "%m/%d/%Y %H:%M"
vector<string> value_column_name = vector<string>({"value"});  // the interesting attributes to be used in TIRPs discovering
*/ //ASL
string result_file_name = "asl_result_file.csv";
string filepath = R"(../datasets/asl_ds.csv)";
string sid_column = "Session_Scene";
string date_column_name_start = "Start";
string date_column_name_end = "End";
string date_format = "%m/%d/%Y %H:%M";
vector<string> value_column_name = vector<string>({"Main_New_Gloss","D_Start_HS","D_End_HS","Passive_Arm"});
/* //HAR
string result_file_name = "har_result_file.csv";
string filepath = R"(../datasets/HAR.csv)";
string sid_column = "subject";
string date_column_name_start = "time";
string date_column_name_end = "time";
string date_format = "%m/%d/%Y %H:%M";
vector<string> value_column_name = vector<string>({"BodyAcc","GravityAcc","BodyGyro","Activity"});
*/

bool avoid_same_var_states = false;
time_type ming = 0;  // minimum gap in seconds that is the gap between before consecutive elements
time_type maxg = 3155695200;  // maximum gap in seconds that is the gap between before consecutive elements
time_type mind = 0;  // each event interval should have a duration of at least min_duration seconds
time_type maxd = 3155695200;   // each tirp should have a duration of at most min_duration seconds
string ps = "mocfbes";

Chrono timeChrono;
int main () {
    vector<LinkedList> list_of_ti_users = vector<LinkedList>();
    vector<string> list_of_users = vector<string>();
    utils_tiRead(filepath, sep, sid_column, date_column_name_start, date_column_name_end,
                                       date_format, value_column_name, list_of_users,list_of_ti_users,timemode_number);


    int nthreads, tid;

/* Fork a team of threads with each thread having a private tid variable */
#pragma omp parallel default(none) shared(nthreads) private(tid)
    {

        /* Obtain and print thread id */
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

        /* Only master thread does this */
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }

    }  /* All threads join master thread and terminate */



    VertTIRP co = VertTIRP(result_file_name,ver_sup,eps,ming,maxg,mind,maxd,dummy,ps,trans);
    timeChrono.start("Compute time");
    int tirp_count = co.mine_patterns(list_of_ti_users,list_of_users,avoid_same_var_states);
    timeChrono.stop("Compute time");
    timeChrono.print();
    co.print_patterns(false);
    cout << "Algorithm finished" << endl;
    return 0;
}
//
// Created by pauca on 31/05/2022.
//

#ifndef VERTTIRP_C_GLOBAL_CPP
#define VERTTIRP_C_GLOBAL_CPP
#include <iostream>

#define TIME_MODE_NUMBER TRUE   //1 timesrtamp, 2 number


typedef long long int time_type;
//#if TIME_MODE_NUMBER TRUE
//typedef unsigned int time_type
//#endif
typedef float support_type;
typedef float eps_type;


using namespace std;

const time_type MAXGAP = 3155695200;
const string NONE = "N";
const string EMPTY = "";
const unsigned UNITS_NUMBER[6] = {1,60,60 * 60,60 * 60 * 24, 60 * 60 * 24 * 7, 60 * 60 * 24 * 365};
const string UNITS_STRING[6] = {"seconds", "minutes", "hours", "days", "weeks", "years"};



#endif //VERTTIRP_C_GLOBAL_CPP

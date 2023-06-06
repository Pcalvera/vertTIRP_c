#ifndef VERTTIRP_C_GLOBAL_CPP
#define VERTTIRP_C_GLOBAL_CPP
#include <iostream>
#include <memory>
#include "Relation.h"
#include "Chrono.h"

typedef double time_type;
typedef double dif_time_type;
typedef float support_type;
typedef float eps_type;
static int n_threads = 1;

using namespace std;

const time_type MAXGAP = 3155695200;
const string NONE = "N";
const string EMPTY = "";
const unsigned UNITS_NUMBER[6] = {1,60,60 * 60,60 * 60 * 24, 60 * 60 * 24 * 7, 60 * 60 * 24 * 365};
const string UNITS_STRING[6] = {"seconds", "minutes", "hours", "days", "weeks", "years"};
const shared_ptr<vector<string>> grArr_nullPtr = nullptr;
const shared_ptr<PairingStrategy> relsArr_nullPtr = nullptr;
//extern Chrono timeChrono;
#endif //VERTTIRP_C_GLOBAL_CPP

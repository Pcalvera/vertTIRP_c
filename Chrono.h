//
// Created by pauca on 10/08/2022.
//

#ifndef VERTTIRP_C_CHRONO_CPP
#define VERTTIRP_C_CHRONO_CPP
#include <iostream>
#include <iomanip>
#include <chrono>
#include "map"
using namespace std;
class Chrono {
public:
    Chrono();
    void start(string name);
    void stop(string name);
    void print()const;

    map<string,double> t;
    map<string,chrono::time_point<chrono::high_resolution_clock>> taux;
};


#endif //VERTTIRP_C_CHRONO_CPP

//
// Created by pauca on 30/03/2022.
//

#ifndef VERTTIRP_C_ALLEN_H
#define VERTTIRP_C_ALLEN_H
#include <iostream>
#include "PairingStrategy.h"
#include "Allen_relationsEPS.cpp"

using namespace std;

class Allen {
public:
    Allen();
    Allen(bool dummy_calc, bool trans = true, float eps = 0, string calc_sort="bselfmoc");

private:
    string calc_sort;
    bool dummy_calc;
    bool trans;
    float eps;
};


#endif //VERTTIRP_C_ALLEN_H

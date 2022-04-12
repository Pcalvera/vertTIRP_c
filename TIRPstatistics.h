//
// Created by pauca on 10/04/2022.
//

#ifndef VERTTIRP_C_TIRPSTATISTICS_H
#define VERTTIRP_C_TIRPSTATISTICS_H
#include <iostream>
#include "TIRP.h"
#include "map"

using namespace std;

class TIRPstatistics {
public:
    TIRPstatistics();
    void append_tirp(string seq_id, unsigned eid, TIRP tirp );

    unsigned get_sum_ver_supp() const;
    float get_mean_hor_support(map<string, unsigned int> &events_per_sequence) const;
    float get_ver_support(unsigned i) const;

};


#endif //VERTTIRP_C_TIRPSTATISTICS_H

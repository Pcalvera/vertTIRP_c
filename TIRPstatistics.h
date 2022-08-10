//
// Created by pauca on 10/04/2022.
//

#ifndef VERTTIRP_C_TIRPSTATISTICS_H
#define VERTTIRP_C_TIRPSTATISTICS_H
#include <iostream>
#include "TIRP.h"
#include "Global.cpp"
#include "Utils.h"
#include "map"
#include "vector"

using namespace std;

class TIRPstatistics {
public:
    TIRPstatistics();
    unsigned append_tirp(string seq_id, unsigned eid, shared_ptr<TIRP> &tirp );

    unsigned get_sum_ver_supp() const;
    support_type get_mean_hor_support(const map<string, unsigned int> &events_per_sequence) const; //TODO float o double
    support_type get_ver_support(unsigned n_sequences) const;
    vector<time_type> get_mean_duration();
    string get_mean_of_means_duration(unsigned units=2);
    map<string,map<unsigned,vector<shared_ptr<TIRP>>>> get_sequence_events_tirps_dict();
private:
    map<string,map<unsigned,vector<shared_ptr<TIRP>>>> sequence_events_tirps_dict;
    unsigned sum_ver_supp;
    map<string,unsigned> sum_hor_per_seq;   //TODO unsigned?
    string last_modified;
    vector<time_type> sum_mean_duration;
    vector<unsigned> n_instances_per_seq;
    vector<time_type> mean_duration;
};


#endif //VERTTIRP_C_TIRPSTATISTICS_H

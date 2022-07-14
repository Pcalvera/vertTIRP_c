//
// Created by pauca on 10/04/2022.
//

#ifndef VERTTIRP_C_TIRPSTATISTICS_H
#define VERTTIRP_C_TIRPSTATISTICS_H
#include <iostream>
#include "TIRP.h"
#include "Utils.h"
#include "map"
#include "vector"
const string EMPTY = "";
static unsigned UNITS_NUMBER[6] = {1,60,60 * 60,60 * 60 * 24, 60 * 60 * 24 * 7, 60 * 60 * 24 * 365}; //TODO comprovar que hagi de ser static
static string UNITS_STRING[6] = {"seconds", "minutes", "hours", "days", "weeks", "years"};

using namespace std;

class TIRPstatistics {
public:
    TIRPstatistics();
    unsigned append_tirp(string seq_id, unsigned eid, TIRP &tirp );

    float get_sum_ver_supp() const;
    float get_mean_hor_support(const map<string, unsigned int> &events_per_sequence) const; //TODO float o double
    float get_ver_support(unsigned n_sequences) const;
    vector<long long> get_mean_duration();
    string get_mean_of_means_duration(unsigned units=2);
    map<string,map<unsigned,vector<TIRP>>> get_sequence_events_tirps_dict();
private:
    map<string,map<unsigned,vector<TIRP>>> sequence_events_tirps_dict;
    unsigned sum_ver_supp;
    map<string,unsigned> sum_hor_per_seq;   //TODO unsigned?
    string last_modified;
    vector<long long> sum_mean_duration;  //TODO long long pq TI utilitza aquest tipus pel temps
    vector<unsigned> n_instances_per_seq;
    vector<long long> mean_duration;
};


#endif //VERTTIRP_C_TIRPSTATISTICS_H

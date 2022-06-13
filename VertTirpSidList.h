//
// Created by pauca on 10/04/2022.
//

#ifndef VERTTIRP_C_VERTTIRPSIDLIST_H
#define VERTTIRP_C_VERTTIRPSIDLIST_H
#include <iostream>
#include "TI.h"
#include "TIRP.h"
#include "TIRPstatistics.h"
#include "map"
#include "vector"
#include "list"

using namespace std;

const long long MAXDURATION = 3155695200;

class VertTirpSidList {
public:
    VertTirpSidList();
    void append_item(TI ti, string sid, unsigned eid);
    void set_n_sequences(int n_sequences);
    float get_mean_hor_support(map<string,unsigned> &events_per_sequence,TIRPstatistics &tirp_stat) const;   //TODO float o double?
    float get_ver_support(TIRPstatistics &tirp) const;                            //TODO float o double?
    unsigned get_support() const;                                                 //TODO comprovar que sigui unsigned
    vector<string> get_seq_str()const;      //TODO retornar ref?
    unsigned get_seq_length()const;
    map<string,map<unsigned,list<TIRP>>> get_definitive_ones_indices_dict()const;
    map<string,TIRPstatistics> get_definitive_discovered_tirp_dict()const;
    VertTirpSidList join(VertTirpSidList f, Allen ps, float eps, int min_gap = 0, int max_gap = MAXGAP, long long max_duration = MAXDURATION, float min_ver_sup = 0, int min_confidence = 0.9)const;
    //TODO join
    //TODO update_tirp_attrs
    //TODO first_sorted_extend

private:
    vector<string> seq_str;
    map<string,map<unsigned,list<TIRP>>> definitive_ones_indices_dict;
    map<string,TIRPstatistics> definitive_discovered_tirp_dict;  //TODO
    //temp_discovered_tirp_dict;  //TODO
    //unsigned seq_length;  //TODO
    unsigned n_sequences;
    unsigned support;

};

#endif //VERTTIRP_C_VERTTIRPSIDLIST_H

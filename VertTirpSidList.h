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

class VertTirpSidList {
public:
    VertTirpSidList();
    void append_item(TI ti, string sid, unsigned eid);
    void set_n_sequences(int n_sequences);
    float get_mean_hor_support(map<string,unsigned> &events_per_sequence,TIRPstatistics &tirp_stat) const;   //TODO float o double?
    float get_ver_support(TIRPstatistics &tirp) const;                            //TODO float o double?
    unsigned get_support() const;                                                 //TODO comprovar que sigui unsigned
    vector<string> get_seq_str()const;      //TODO retornar ref?
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

};

#endif //VERTTIRP_C_VERTTIRPSIDLIST_H

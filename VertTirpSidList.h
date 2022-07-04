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
    map<string,map<unsigned,vector<TIRP>>> get_definitive_ones_indices_dict()const;
    map<string,TIRPstatistics> get_definitive_discovered_tirp_dict()const;
    VertTirpSidList join(VertTirpSidList f, Allen ps, float eps, long long min_gap = 0, long long max_gap = MAXGAP, long long max_duration = MAXDURATION, float min_ver_sup = 0, int min_confidence = 0.9)const;
    unsigned update_tirp_attrs(const string &seq_id, unsigned f_eid, VertTirpSidList &f_sidlist, bool mine_last_equal, const Allen &ps, const vector<TIRP> &tirps_to_extend, float eps, long long  min_gap, long long  max_gap, long long int max_duration, float min_ver_sup, map<string,TIRPstatistics> &father_discovered_tirp_dict, int min_confidence);
    //TODO first_sorted_extend

private:
    vector<string> seq_str;
    map<string,map<unsigned,vector<TIRP>>> definitive_ones_indices_dict; //TODO comprovar que hagi de ser un vector i no list
    map<string,TIRPstatistics> definitive_discovered_tirp_dict;  //TODO
    map<string,TIRPstatistics> temp_discovered_tirp_dict;  //TODO
    //unsigned seq_length;  //TODO
    unsigned n_sequences;
    unsigned support;

};

#endif //VERTTIRP_C_VERTTIRPSIDLIST_H

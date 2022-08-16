//
// Created by pauca on 10/04/2022.
//

#ifndef VERTTIRP_C_VERTTIRPSIDLIST_H
#define VERTTIRP_C_VERTTIRPSIDLIST_H
#include <iostream>
#include "Chrono.h"
#include "Global.h"
#include "TI.h"
#include "TIRP.h"
#include "TIRPstatistics.h"
#include "map"
#include "vector"
#include "list"

using namespace std;

const time_type MAXDURATION = 3155695200;

class VertTirpSidList {
public:
    VertTirpSidList();
    void append_item(TI *ti, string sid, unsigned eid);
    void set_n_sequences(int n_sequences);
    support_type get_mean_hor_support(const map<string,unsigned> &events_per_sequence,const shared_ptr<TIRPstatistics> &tirp_stat) const;
    support_type get_ver_support(const shared_ptr<TIRPstatistics> &tirp) const;
    unsigned get_support() const;
    vector<string>& get_seq_str();
    unsigned get_seq_length()const;
    map<string,map<unsigned,vector<shared_ptr<TIRP>>>>& get_definitive_ones_indices_dict();
    map<string,shared_ptr<TIRPstatistics>>& get_definitive_discovered_tirp_dict();
    VertTirpSidList join(VertTirpSidList &f, Allen &ps, eps_type eps, time_type min_gap = 0, time_type max_gap = MAXGAP, time_type max_duration = MAXDURATION, support_type min_ver_sup = 0, float min_confidence = 0.9);
    unsigned update_tirp_attrs(const string &seq_id, unsigned f_eid, VertTirpSidList &f_sidlist, bool mine_last_equal, Allen &ps, const vector<shared_ptr<TIRP>> &tirps_to_extend, eps_type eps, time_type  min_gap, time_type  max_gap, time_type max_duration, support_type min_ver_sup, const map<string,shared_ptr<TIRPstatistics>>  &father_discovered_tirp_dict, float min_confidence,double &temps);
    void first_sorted_extend(const string &sid, unsigned eid, const vector<shared_ptr<TIRP>> &new_tirps);

private:
    vector<string> seq_str;
    map<string,map<unsigned,vector<shared_ptr<TIRP>>>> definitive_ones_indices_dict;
    map<string,shared_ptr<TIRPstatistics>> definitive_discovered_tirp_dict;
    map<string,shared_ptr<TIRPstatistics>> temp_discovered_tirp_dict;
    unsigned n_sequences;
    unsigned support;
    Chrono chrono;
};

#endif //VERTTIRP_C_VERTTIRPSIDLIST_H

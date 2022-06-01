//
// Created by pauca on 10/04/2022.
//

#include "VertTirpSidList.h"

VertTirpSidList::VertTirpSidList() {
    //TODO comentaris
    this->seq_str = vector<string>();
    this->definitive_ones_indices_dict = map<string,map<unsigned,list<TIRP>>>();
    this->definitive_discovered_tirp_dict = map<string,TIRPstatistics>();  //TODO
    //temp_discovered_tirp_dict = map<>();  //TODO
    this->n_sequences = 0;
}

void VertTirpSidList::append_item(TI ti, string sid, unsigned eid) {
    //TODO comentaris
    TIRP new_tirp =  TIRP(vector<TI>(1,ti), ti.get_start(), ti.get_end() );  //TODO inicialitzar amb 1?

    if ( this->definitive_discovered_tirp_dict.empty() ){
        this->definitive_discovered_tirp_dict.insert(pair<string,TIRPstatistics>("",TIRPstatistics()));
        this->seq_str.push_back(ti.get_sym());
    }

    auto doid_it = this->definitive_ones_indices_dict.find(sid);
    if ( doid_it == definitive_ones_indices_dict.end() )
        doid_it = this->definitive_ones_indices_dict.insert(pair<string,map<unsigned,list<TIRP>>>(sid,map<unsigned,list<TIRP>>() ) ).first;

    this->definitive_discovered_tirp_dict.find("")->second.append_tirp(sid,eid,new_tirp); //TODO potser es pot fer abans

    auto doid_it2 = doid_it->second.find(eid);
    if ( doid_it2 == doid_it->second.end() )
        doid_it->second.insert(pair<unsigned,list<TIRP>>(eid,list<TIRP>(1,new_tirp)));
    else
        doid_it2->second.push_back(new_tirp);
}

void VertTirpSidList::set_n_sequences(int n_sequences) {
    //TODO comentaris
    this->n_sequences = n_sequences;
}

float VertTirpSidList::get_mean_hor_support(map<string, unsigned int> &events_per_sequence, TIRPstatistics &tirp_stat) const {
    //TODO comentaris
    return tirp_stat.get_mean_hor_support(events_per_sequence);
}

float VertTirpSidList::get_ver_support(TIRPstatistics &tirp) const{
    //TODO comentaris
    return tirp.get_ver_support(this->n_sequences);
}

unsigned VertTirpSidList::get_support() const {
    //TODO comentaris
    return this->definitive_discovered_tirp_dict.find("")->second.get_sum_ver_supp();
}

vector<string> VertTirpSidList::get_seq_str() const {
    return this->seq_str;
}


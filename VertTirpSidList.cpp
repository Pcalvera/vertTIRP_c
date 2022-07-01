//
// Created by pauca on 10/04/2022.
//

#include "VertTirpSidList.h"

VertTirpSidList::VertTirpSidList() {
    //TODO comentaris
    this->seq_str = vector<string>();
    this->definitive_ones_indices_dict = map<string,map<unsigned,vector<TIRP>>>();
    this->definitive_discovered_tirp_dict = map<string,TIRPstatistics>();  //TODO
    //temp_discovered_tirp_dict = map<>();  //TODO
    this->n_sequences = 0;
    this->support = 0;
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
        doid_it = this->definitive_ones_indices_dict.insert(pair<string,map<unsigned,vector<TIRP>>>(sid,map<unsigned,vector<TIRP>>() ) ).first;

    this->definitive_discovered_tirp_dict.find("")->second.append_tirp(sid,eid,new_tirp); //TODO potser es pot fer abans

    auto doid_it2 = doid_it->second.find(eid);
    if ( doid_it2 == doid_it->second.end() )
        doid_it->second.insert(pair<unsigned,vector<TIRP>>(eid,vector<TIRP>(1,new_tirp)));
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

unsigned VertTirpSidList::get_seq_length() const {
    return this->seq_str.size();
}

map<string, map<unsigned, vector<TIRP>>> VertTirpSidList::get_definitive_ones_indices_dict() const {
    return this->definitive_ones_indices_dict;
}

map<string, TIRPstatistics> VertTirpSidList::get_definitive_discovered_tirp_dict() const {
    return this->definitive_discovered_tirp_dict;
}

VertTirpSidList VertTirpSidList::join(VertTirpSidList f, Allen ps, float eps, long long  min_gap, long long  max_gap,
                                      long long int max_duration, float min_ver_sup, int min_confidence) const {
    //TODO comentaris
    VertTirpSidList new_sidlist = VertTirpSidList();   //TODO potser millor fer un constructor amb tots els paràmetres
    new_sidlist.seq_str = vector<string>(this->seq_str);
    new_sidlist.seq_str.push_back(f.seq_str[0]);

    new_sidlist.n_sequences = this->n_sequences;

    bool mine_last_equal = this->seq_str.back() < f.seq_str[0];

    // TODO for
    for ( const auto& item : this->definitive_ones_indices_dict ){
        string seq_id = item.first;
        map<unsigned,vector<TIRP>> dict_pos_tirps = item.second;
        if ( f.definitive_ones_indices_dict.find(seq_id) != f.definitive_ones_indices_dict.end() ) {
            //vector<int> f_eids = utils_getKeys(f.definitive_ones_indices_dict[seq_id]);   //TODO fer funcionar la funcio
            vector<unsigned> f_eids = vector<unsigned>();
            for (auto it: f.definitive_ones_indices_dict[seq_id])
                f_eids.push_back(it.first);
            //TODO fi

            long long last_f_first = f.definitive_ones_indices_dict[seq_id][f_eids.back()][0].get_first();
            long long first_f_first = f.definitive_ones_indices_dict[seq_id][f_eids.front()][0].get_first();
            for (const auto &item2: dict_pos_tirps) {
                unsigned self_first_eid = item2.first;
                vector<TIRP> self_tirps = item2.second;
                // if there exists eids in f greater than my first eid
                if (self_first_eid < f_eids.back()) {

                    // first tirp
                    TIRP first_one_me = self_tirps.front();
                    // first tirp's start time
                    long long me_first = first_one_me.get_first();

                    // determine from which point in time start to search
                    if ( min_gap > 0 )
                        me_first = first_one_me.get_first() + min_gap;
                    // if last element of f, sidlist matchs the min gap restriction
                    if ( last_f_first >= me_first ){
                        long long me_second;
                        if ( max_gap != MAXGAP )
                            me_second
                    }
                }
            }
        }
    }
    //TODO del temps_idscovered_tirp_dict
    return new_sidlist;
}


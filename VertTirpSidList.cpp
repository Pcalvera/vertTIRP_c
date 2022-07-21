//
// Created by pauca on 10/04/2022.
//

#include "VertTirpSidList.h"

VertTirpSidList::VertTirpSidList() {
    this->seq_str = vector<string>();
    this->definitive_ones_indices_dict = map<string,map<unsigned,vector<TIRP>>>();
    this->definitive_discovered_tirp_dict = map<string,TIRPstatistics>();
    this->temp_discovered_tirp_dict = map<string,TIRPstatistics>();
    this->n_sequences = 0;
    this->support = 0;
}

void VertTirpSidList::append_item(const TI &ti, string sid, unsigned eid) {
    TIRP new_tirp =  TIRP(vector<TI>(1,ti), ti.get_start(), ti.get_end() );  //TODO inicialitzar amb 1?

    if ( this->definitive_discovered_tirp_dict.empty() ){
        //this->definitive_discovered_tirp_dict.insert(pair<string,TIRPstatistics>(EMPTY,TIRPstatistics()));    //TODO []
        this->definitive_discovered_tirp_dict[EMPTY] = TIRPstatistics();
        this->seq_str.push_back(ti.get_sym());
    }

    auto doid_it = this->definitive_ones_indices_dict.find(sid);
    if ( doid_it == definitive_ones_indices_dict.end() )
        doid_it = this->definitive_ones_indices_dict.insert(pair<string,map<unsigned,vector<TIRP>>>(sid,map<unsigned,vector<TIRP>>() ) ).first;

    //this->definitive_discovered_tirp_dict.find("")->second.append_tirp(sid,eid,new_tirp); //TODO potser es pot fer abans,    canviar per at()
    this->definitive_discovered_tirp_dict.at(EMPTY).append_tirp(sid,eid,new_tirp);

    auto doid_it2 = doid_it->second.find(eid);
    if ( doid_it2 == doid_it->second.end() )
        doid_it->second.insert(pair<unsigned,vector<TIRP>>(eid,vector<TIRP>(1,new_tirp)));
    else
        doid_it2->second.push_back(new_tirp);
}

void VertTirpSidList::set_n_sequences(int n_sequences) {
    this->n_sequences = n_sequences;
}

support_type VertTirpSidList::get_mean_hor_support(const map<string, unsigned int> &events_per_sequence,const TIRPstatistics &tirp_stat) const {
    return tirp_stat.get_mean_hor_support(events_per_sequence);
}

support_type VertTirpSidList::get_ver_support(const TIRPstatistics &tirp) const{
    return tirp.get_ver_support(this->n_sequences);
}

unsigned VertTirpSidList::get_support() const {
    return this->definitive_discovered_tirp_dict.find(EMPTY)->second.get_sum_ver_supp();
}

vector<string> VertTirpSidList::get_seq_str() const{
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

VertTirpSidList VertTirpSidList::join(const VertTirpSidList &f, const Allen &ps, eps_type eps, time_type min_gap, time_type  max_gap,
                                      time_type max_duration, support_type min_ver_sup, int min_confidence) {
    VertTirpSidList new_sidlist = VertTirpSidList();   //TODO potser millor fer un constructor amb tots els paràmetres
    new_sidlist.seq_str = vector<string>(this->seq_str);
    new_sidlist.seq_str.push_back(f.seq_str[0]);

    new_sidlist.n_sequences = this->n_sequences;

    bool mine_last_equal = this->seq_str.back() < f.seq_str[0];


    for ( const auto& item : this->definitive_ones_indices_dict ){
        string seq_id = item.first;
        map<unsigned,vector<TIRP>> dict_pos_tirps = item.second;
        if ( f.definitive_ones_indices_dict.find(seq_id) != f.definitive_ones_indices_dict.end() ) {
            //vector<int> f_eids = utils_getKeys(f.definitive_ones_indices_dict[seq_id]);   //TODO fer funcionar la funcio
            vector<unsigned> f_eids = vector<unsigned>();
            for (const auto &it: f.definitive_ones_indices_dict.at(seq_id))
                f_eids.push_back(it.first);
            //TODO fi

            time_type last_f_first = f.definitive_ones_indices_dict.at(seq_id).at(f_eids.back())[0].get_first();
            time_type first_f_first = f.definitive_ones_indices_dict.at(seq_id).at(f_eids.front())[0].get_first();
            for (const auto &item2: dict_pos_tirps) {
                unsigned self_first_eid = item2.first;
                vector<TIRP> self_tirps = item2.second;
                // if there exists eids in f greater than my first eid
                if (self_first_eid < f_eids.back()) {

                    // first tirp
                    TIRP first_one_me = self_tirps.front();
                    // first tirp's start time
                    time_type me_first = first_one_me.get_first();

                    // determine from which point in time start to search
                    if ( min_gap > 0 )
                        me_first = first_one_me.get_first() + min_gap;
                    // if last element of f, sidlist matchs the min gap restriction
                    if ( last_f_first >= me_first ){
                        time_type me_second;
                        bool me_second_init = false;
                        if ( max_gap != MAXGAP ) {
                            me_second = me_first + max_gap;
                            me_second_init = true;
                        }
                        if ( max_gap == MAXGAP || ( me_second_init && first_f_first <= me_second ) ){
                             for ( const auto &item3 : f.definitive_ones_indices_dict.at(seq_id) ){
                                 unsigned f_pos = item3.first;
                                 vector<TIRP> f_tirps = item3.second;

                                 if ( me_second_init && f_tirps[0].get_first() > me_second )
                                     break;
                                 else{
                                    if ( f_pos > self_first_eid ){
                                        unsigned exit_status = new_sidlist.update_tirp_attrs(seq_id, f_pos, f, mine_last_equal, ps, self_tirps, eps, min_gap, max_gap, max_duration, min_ver_sup, this->definitive_discovered_tirp_dict, min_confidence);
                                        if ( exit_status == 2 )
                                            // max_gap exceeded for all the tirps, break and continue with another 1 of the self sequence
                                            // no sense prove out the next s event id, as max gap exceeded
                                            break;
                                    }
                                 }
                             }
                        }

                    }
                }
            }
        }
    }
    this->temp_discovered_tirp_dict = map<string,TIRPstatistics>();
    return new_sidlist;
}

unsigned VertTirpSidList::update_tirp_attrs(const string &seq_id, unsigned int f_eid, const VertTirpSidList &f_sidlist,
                                            bool mine_last_equal, const Allen &ps, const vector<TIRP> &tirps_to_extend,
                                            eps_type eps, time_type min_gap, time_type  max_gap,
                                            time_type max_duration, support_type min_ver_sup,
                                            const map<string, TIRPstatistics> &father_discovered_tirp_dict,
                                            int min_confidence) {
    vector<TI> f_ti = f_sidlist.definitive_ones_indices_dict.at(seq_id).at(f_eid)[0].get_ti();

    bool all_max_gap_exceeded = true;
    bool at_least_one_tirp = false;

    for ( const TIRP &tirp_to_extend : tirps_to_extend ){
        // the extension will return a new tirp and a status
        // status is: if ok:3, fi max_gap:2, otherwise:1
        pair<pair<bool,TIRP>,unsigned> extended_tirp = tirp_to_extend.extend_with(f_ti[0],eps,min_gap,max_gap,max_duration,mine_last_equal,ps);

        if ( extended_tirp.first.first ){
            at_least_one_tirp = true;

            string new_rel = extended_tirp.first.second.get_rel_as_str();
            /*
            if ( this->temp_discovered_tirp_dict.find(new_rel) == this->temp_discovered_tirp_dict.end() )
                // create
                this->temp_discovered_tirp_dict[new_rel] = TIRPstatistics();
                */  //TODO crec que ja es crea automaticament amb el constructor default a la linia d'abaix

            // append it to a temporal discovered
            unsigned vert_supp = this->temp_discovered_tirp_dict[new_rel].append_tirp( seq_id,f_eid,extended_tirp.first.second );

            // confidence calculation
            bool conf_constraint = true;
            if ( min_confidence != -1 ){
                support_type father_supp;
                if ( tirp_to_extend.get_rel_as_str() == EMPTY )
                    father_supp = father_discovered_tirp_dict.at(EMPTY).get_sum_ver_supp();  //TODO retorna unsigned
                else
                    father_supp = father_discovered_tirp_dict.at(tirp_to_extend.get_rel_as_str()).get_sum_ver_supp(); //TODO retorna unsigned
                conf_constraint = ((float)vert_supp / father_supp) >= (float)min_confidence; // TODO comprovar conversio unsigned float
            }

            if ( (float)vert_supp >= min_ver_sup && conf_constraint ){
                auto new_rel_in_definitive_disc_tirp_dict = this->definitive_discovered_tirp_dict.find(new_rel);
                if ( new_rel_in_definitive_disc_tirp_dict != this->definitive_discovered_tirp_dict.end() ){
                    // if the new_rel exists in the this->definitive_discovered_tirp_dict
                    new_rel_in_definitive_disc_tirp_dict->second = this->temp_discovered_tirp_dict.at(new_rel);

                    // update this->definitive_ones_indices_dict with a new_tirp
                    this->definitive_ones_indices_dict[seq_id];
                    this->definitive_ones_indices_dict[seq_id][f_eid];

                    auto it = this->definitive_ones_indices_dict.find(seq_id);
                    if ( it == this->definitive_ones_indices_dict.end() )
                        it->second[f_eid] = vector<TIRP>(1,extended_tirp.first.second);
                    else
                        this->first_sorted_extend(seq_id, f_eid, vector<TIRP>(1,extended_tirp.first.second));
                }
                else {
                    // If the new_rel does not exists in the self.definitive_discovered_tirp_dict
                    // what means that the new_rel just became frequent
                    this->definitive_discovered_tirp_dict[new_rel] = this->temp_discovered_tirp_dict.at(new_rel);

                    // copy all the frequent tirps at the correspondent event ids of
                    // self.definitive_ones_indices_dict
                    for ( const auto &sid_eidtirps : this->definitive_discovered_tirp_dict.at(new_rel).get_sequence_events_tirps_dict()){
                        string sid = sid_eidtirps.first;
                        for ( const auto &eid_tirps : sid_eidtirps.second ){
                            unsigned eid = eid_tirps.first;
                            auto it2 = this->definitive_ones_indices_dict.find(sid);
                            if ( it2 == this->definitive_ones_indices_dict.end() ){
                                this->support++;
                                it2 = this->definitive_ones_indices_dict.insert(pair<string,map<unsigned,vector<TIRP>>>(
                                        sid,
                                        map<unsigned,vector<TIRP>>()
                                        )).first;
                            }

                            auto it3 = it2->second.find(eid);
                            if ( it3 == it2->second.end() )
                                it2->second.insert(pair<unsigned,vector<TIRP>>(
                                        eid,
                                        vector<TIRP>(eid_tirps.second)));
                            else
                                this->first_sorted_extend(sid,eid, eid_tirps.second);
                        }
                    }
                }
            }
        }
        else if ( extended_tirp.second != 2 )
            all_max_gap_exceeded = false;
    }

    if ( at_least_one_tirp )
        return 3;
    else if ( all_max_gap_exceeded )
        return 2;
    else
        return 1;
}

void VertTirpSidList::first_sorted_extend(const string &sid, unsigned eid, const vector<TIRP> &new_tirps) {
    //TODO comentaris

    vector<TIRP> &current_tirps = this->definitive_ones_indices_dict[sid][eid];
    unsigned i = 0;
    unsigned j = new_tirps.size();
    while ( i < j ){
        //if ( new_tirps[i].get_max_last() > current_tirps.front().get_max_last() ) //TODO afegir al principi i mirar si definitive_ones_indices_dict ha de ser llista
            current_tirps.push_back(new_tirps[i]);
            i++;
    }
}







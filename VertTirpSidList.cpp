#include "VertTirpSidList.h"

VertTirpSidList::VertTirpSidList() {
    this->seq_str = vector<string>();
    this->definitive_ones_indices_dict = map<string,map<unsigned,vector<shared_ptr<TIRP>>>>();
    this->definitive_discovered_tirp_dict = map<string,shared_ptr<TIRPstatistics>>();
    this->temp_discovered_tirp_dict = map<string,shared_ptr<TIRPstatistics>>();
    this->n_sequences = 0;
    this->support = 0;
}

void VertTirpSidList::append_item(TI *ti, string sid, unsigned eid) {
    shared_ptr<TIRP> new_tirp =  make_shared<TIRP>(vector<TI*>(1,ti), ti->get_start(), ti->get_end() );

    if ( this->definitive_discovered_tirp_dict.empty() ){
        this->definitive_discovered_tirp_dict[EMPTY] = std::make_shared<TIRPstatistics>( );
        this->seq_str.push_back(ti->get_sym());
    }

    auto doid_it = this->definitive_ones_indices_dict.find(sid);
    if ( doid_it == definitive_ones_indices_dict.end() )
        doid_it = this->definitive_ones_indices_dict.insert(pair<string,map<unsigned,vector<shared_ptr<TIRP>>>>(sid,map<unsigned,vector<shared_ptr<TIRP>>>() ) ).first;

    this->definitive_discovered_tirp_dict.at(EMPTY)->append_tirp(sid,eid,new_tirp);

    auto doid_it2 = doid_it->second.find(eid);
    if ( doid_it2 == doid_it->second.end() )
        doid_it->second.insert(pair<unsigned,vector<shared_ptr<TIRP>>>(eid,vector<shared_ptr<TIRP>>(1, new_tirp )));
    else
        doid_it2->second.emplace_back(new_tirp);
}

void VertTirpSidList::set_n_sequences(int n_sequences) {
    this->n_sequences = n_sequences;
}

support_type VertTirpSidList::get_mean_hor_support(const map<string, unsigned int> &events_per_sequence,const shared_ptr<TIRPstatistics> &tirp_stat) const {
    return tirp_stat->get_mean_hor_support(events_per_sequence);
}

support_type VertTirpSidList::get_ver_support(const shared_ptr<TIRPstatistics> &tirp) const{
    return tirp->get_ver_support(this->n_sequences);
}

unsigned VertTirpSidList::get_support() const {
    return this->definitive_discovered_tirp_dict.at(EMPTY)->get_sum_ver_supp();
}

vector<string>& VertTirpSidList::get_seq_str() {
    return this->seq_str;
}

unsigned VertTirpSidList::get_seq_length() const {
    return this->seq_str.size();
}

map<string, map<unsigned, vector<shared_ptr<TIRP>>>>& VertTirpSidList::get_definitive_ones_indices_dict() {
    return this->definitive_ones_indices_dict;
}

map<string, shared_ptr<TIRPstatistics>>& VertTirpSidList::get_definitive_discovered_tirp_dict() {
    return this->definitive_discovered_tirp_dict;
}

VertTirpSidList VertTirpSidList::join(VertTirpSidList &f,  Allen &ps, eps_type eps, time_type min_gap, time_type  max_gap,
                                      time_type max_duration, support_type min_ver_sup, float min_confidence) {
    VertTirpSidList new_sidlist = VertTirpSidList();
    new_sidlist.seq_str = vector<string>(this->seq_str);
    new_sidlist.seq_str.push_back(f.seq_str[0]);

    new_sidlist.n_sequences = this->n_sequences;
    bool mine_last_equal = this->seq_str.back() < f.seq_str[0];
    for ( auto& item : this->definitive_ones_indices_dict ){

        string seq_id = item.first;
        map<unsigned,vector<shared_ptr<TIRP>>> dict_pos_tirps = item.second;
        auto f_at_seq_id = f.definitive_ones_indices_dict.find(seq_id);
        if ( f_at_seq_id != f.definitive_ones_indices_dict.end() ) {

            vector<unsigned> f_eids = vector<unsigned>();
            for (const auto &it: f_at_seq_id->second)
                f_eids.push_back(it.first);

            time_type last_f_first = f_at_seq_id->second.at(f_eids.back())[0]->get_first();
            time_type first_f_first = f_at_seq_id->second.at(f_eids.front())[0]->get_first();
            for (auto &item2: dict_pos_tirps) {

                unsigned self_first_eid = item2.first;
                vector<shared_ptr<TIRP>> &self_tirps = item2.second;
                // if there exists eids in f greater than my first eid
                if (self_first_eid < f_eids.back()) {

                    // first tirp
                    shared_ptr<TIRP> &first_one_me = self_tirps.front();
                    // first tirp's start time
                    time_type me_first = first_one_me->get_first();

                    // determine from which point in time start to search
                    if ( min_gap > 0 )
                        me_first = first_one_me->get_first() + min_gap;

                    // if last element of f, sidlist matchs the min gap restriction
                    if ( last_f_first >= me_first ){

                        time_type me_second;
                        bool me_second_init = false;
                        if ( max_gap != MAXGAP ) {
                            me_second = me_first + max_gap;
                            me_second_init = true;
                        }
                        if ( max_gap == MAXGAP || ( me_second_init && first_f_first <= me_second ) ){
                            for ( auto &item3 : f.definitive_ones_indices_dict.at(seq_id) ){
                                unsigned f_pos = item3.first;
                                vector<shared_ptr<TIRP>> &f_tirps = item3.second;

                                if ( me_second_init && f_tirps[0]->get_first() > me_second )
                                    break;
                                else{
                                    if ( f_pos > self_first_eid ) {
                                        unsigned exit_status = new_sidlist.update_tirp_attrs(seq_id, f_pos, f,
                                                                                             mine_last_equal, ps,
                                                                                             self_tirps, eps,
                                                                                             min_gap, max_gap,
                                                                                             max_duration,
                                                                                             min_ver_sup,
                                                                                             this->definitive_discovered_tirp_dict,
                                                                                             min_confidence);
                                        if (exit_status == 2)
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
    this->temp_discovered_tirp_dict.clear();
    return new_sidlist;
}

unsigned VertTirpSidList::update_tirp_attrs(const string &seq_id, unsigned int f_eid, VertTirpSidList &f_sidlist,
                                            bool mine_last_equal, Allen &ps, const vector<shared_ptr<TIRP>> &tirps_to_extend,
                                            eps_type eps, time_type min_gap, time_type  max_gap,
                                            time_type max_duration, support_type min_ver_sup,
                                            const map<string,shared_ptr<TIRPstatistics>> &father_discovered_tirp_dict,
                                            float min_confidence) {
    TI** f_ti = f_sidlist.definitive_ones_indices_dict.at(seq_id).at(f_eid)[0]->get_ti();

    bool all_max_gap_exceeded = true;
    bool at_least_one_tirp = false;

    vector<pair<shared_ptr<TIRP>,unsigned>> extended_tirps = vector<pair<shared_ptr<TIRP>,unsigned>>(tirps_to_extend.size());
    int index;
    int tirps_to_extend_size = tirps_to_extend.size();
    TI *f_ti_0 = f_ti[0];

    #pragma omp parallel for default(none) private(index) shared(extended_tirps,tirps_to_extend,tirps_to_extend_size,f_ti_0,eps,min_gap,max_gap,max_duration,mine_last_equal,ps) num_threads(n_threads) schedule(dynamic)
    for ( index = 0 ; index < tirps_to_extend_size ; index++)
        extended_tirps[index] = tirps_to_extend[index]->extend_with(f_ti_0,eps,min_gap,max_gap,max_duration,mine_last_equal,ps);

    for ( index = 0; index<tirps_to_extend_size ; index++ ){
        // the extension will return a new tirp and a status
        // status is: if ok:3, fi max_gap:2, otherwise:1
        pair<shared_ptr<TIRP>,unsigned> &extended_tirp = extended_tirps[index];

        if ( extended_tirp.first != nullptr ){
            at_least_one_tirp = true;

            string new_rel = extended_tirp.first->get_rel_as_str();
            // append it to a temporal discovered
            auto temp_it = this->temp_discovered_tirp_dict.find(new_rel);
            if ( temp_it == this->temp_discovered_tirp_dict.end() )
                temp_it = this->temp_discovered_tirp_dict.insert(make_pair(new_rel,std::make_shared<TIRPstatistics>())).first;
            unsigned vert_supp = temp_it->second->append_tirp( seq_id,f_eid,extended_tirp.first );

            // confidence calculation
            bool conf_constraint = true;
            if ( min_confidence != -1 ){
                support_type father_supp;
                if ( tirps_to_extend[index]->get_rel_as_str() == EMPTY )
                    father_supp = father_discovered_tirp_dict.at(EMPTY)->get_sum_ver_supp();
                else
                    father_supp = father_discovered_tirp_dict.at(tirps_to_extend[index]->get_rel_as_str())->get_sum_ver_supp();
                conf_constraint = ((float)vert_supp / father_supp) >= (float)min_confidence;
            }

            if ( (support_type)vert_supp >= min_ver_sup && conf_constraint ){
                auto new_rel_in_definitive_disc_tirp_dict = this->definitive_discovered_tirp_dict.find(new_rel);
                if ( new_rel_in_definitive_disc_tirp_dict != this->definitive_discovered_tirp_dict.end() ){
                    // if the new_rel exists in the this->definitive_discovered_tirp_dict
                    new_rel_in_definitive_disc_tirp_dict->second = this->temp_discovered_tirp_dict.at(new_rel);
                    // update this->definitive_ones_indices_dict with a new_tirp
                    auto &it = this->definitive_ones_indices_dict[seq_id];
                    //this->definitive_ones_indices_dict[seq_id][f_eid];

                    auto itt = it.find(f_eid);
                    if ( itt == it.end() )
                        it[f_eid] = vector<shared_ptr<TIRP>>(1,extended_tirp.first );
                    else
                        this->first_sorted_extend(seq_id, f_eid, vector<shared_ptr<TIRP>>(1,extended_tirp.first ));
                }
                else {
                    // If the new_rel does not exists in the self.definitive_discovered_tirp_dict
                    // what means that the new_rel just became frequent
                    this->definitive_discovered_tirp_dict[new_rel] = this->temp_discovered_tirp_dict.at(new_rel);

                    // copy all the frequent tirps at the correspondent event ids of
                    // self.definitive_ones_indices_dict
                    for ( const auto &sid_eidtirps : this->definitive_discovered_tirp_dict.at(new_rel)->get_sequence_events_tirps_dict()){
                        string sid = sid_eidtirps.first;
                        for ( const auto &eid_tirps : sid_eidtirps.second ){
                            unsigned eid = eid_tirps.first;
                            auto it2 = this->definitive_ones_indices_dict.find(sid);
                            if ( it2 == this->definitive_ones_indices_dict.end() ){
                                this->support++;
                                it2 = this->definitive_ones_indices_dict.insert(pair<string,map<unsigned,vector<shared_ptr<TIRP>>>>(
                                        sid,
                                        map<unsigned,vector<shared_ptr<TIRP>>>()
                                )).first;
                            }

                            auto it3 = it2->second.find(eid);
                            if ( it3 == it2->second.end() ) {
                                auto inserted = it2->second.insert(pair<unsigned, vector<shared_ptr<TIRP>>>(
                                        eid,
                                        vector<shared_ptr<TIRP>>())).first;
                                for ( auto &copyTirp : eid_tirps.second )
                                    inserted->second.emplace_back(copyTirp);
                            }
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
    //delete []extended_tirps;
    if ( at_least_one_tirp )
        return 3;
    else if ( all_max_gap_exceeded )
        return 2;
    else
        return 1;
}

void VertTirpSidList::first_sorted_extend(const string &sid, unsigned eid, const vector<shared_ptr<TIRP>> &new_tirps) {
    vector<shared_ptr<TIRP>> &current_tirps = this->definitive_ones_indices_dict[sid][eid];
    unsigned i = 0;
    unsigned j = new_tirps.size();
    while ( i < j ){
            current_tirps.emplace_back(new_tirps[i]);
            i++;
    }
}
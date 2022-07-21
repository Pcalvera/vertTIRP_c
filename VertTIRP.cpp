//
// Created by pauca on 30/03/2022.
//

#include "VertTIRP.h"

VertTIRP::VertTIRP(string &out_file, support_type min_sup_rel, eps_type eps, time_type min_gap, time_type max_gap,
                   int min_duration, time_type max_duration, bool dummy_calc, string &ps, bool trans, int min_confidence , int max_length, int min_length) {

    this->out_file = out_file;
    events_per_sequence = map<string,unsigned>();
    this->min_sup_rel = min_sup_rel;
    this->min_confidence = min_confidence;
    this->min_gap = min_gap;
    this->max_gap = max_gap;
    this->min_duration = min_duration;
    this->max_duration = max_duration;
    this->max_length = max_length;
    this->min_length = min_length;
    this->eps = eps;

    this->tirp_count = 0;
    this->min_sup = 0;

    this->f1 = vector<string>();
    this->vertical_db = map<string,VertTirpSidList>();
    this->tree = VertTirpNode();
    time_mode = time_mode;

    if ( min_gap < 0 || max_gap < 0 )
        throw invalid_argument("min_gap and max_gap must have positive values");
    if ( (min_gap != 0 || max_gap != 0) && min_gap >= max_gap )
        throw invalid_argument("max_gap must be greater than min_gap");

    if ( !dummy_calc )
        this->allen = Allen(dummy_calc,trans,eps,ps);
    else
        this->allen = Allen(dummy_calc,trans,eps);
}

int VertTIRP::mine_patterns(vector<vector<TI>> const &list_of_ti_seqs, vector<string> const &list_of_seqs, bool avoid_same_var_states) {
    if ( list_of_ti_seqs.size() != list_of_seqs.size() ) throw invalid_argument("list_of_ti_seqs and list_of_seqs must have the same size");

    this->to_vertical(list_of_ti_seqs,list_of_seqs);
    //TODO taula procs

    for (auto & i : this->f1){
        vector<string> seq_str_strings = this->vertical_db[i].get_seq_str();
        string seq_str_string = utils_unifyStrings(seq_str_strings);
        VertTirpNode s_node = VertTirpNode(seq_str_string,1,this->vertical_db[i],this->tree);
        this->dfs_pruning(this->vertical_db[i],this->f1,s_node,this->tree,avoid_same_var_states);  //TODO fer pruning
    }
    return this->tirp_count;
}

void VertTIRP::print_patterns(bool dfs) {
    this->tree.print_tree(this->min_length, this->out_file, this->events_per_sequence,dfs);
}

bool VertTIRP::same_variable(string s1, string s2, bool avoid_same_var_states) {
    return avoid_same_var_states && s1 == s2;
}

void VertTIRP::dfs_pruning(VertTirpSidList &pat_sidlist, vector<string> &f_l, VertTirpNode &node,VertTirpNode &father, bool avoid_same_var_states ) {
    father.add_child(node);

    if ( pat_sidlist.get_seq_length() >= this->min_length )
        this->tirp_count += pat_sidlist.get_definitive_discovered_tirp_dict().size();

    map<string,VertTirpSidList> s_temp;

    // to control the maximum length
    if ( this->max_length == -1 || (pat_sidlist.get_seq_length() + 1) <= this->max_length ){
        for ( string s : f_l){
            if ( !this->same_variable(s, pat_sidlist.get_seq_str().back(), avoid_same_var_states) ){
                VertTirpSidList s_bm = pat_sidlist.join(this->vertical_db[s], this->allen, this->eps, this->min_gap, this->max_gap, this->max_duration, this->min_sup, this->min_confidence);
                if ( !s_bm.get_definitive_ones_indices_dict().empty() )
                    s_temp[s] = s_bm;
            }
        }
        //vector<string> s_syms = utils_getKeys(s_temp);   //TODO fer funcionar la funcio
        vector<string> s_syms =  vector<string>();
        for ( auto it : s_temp)
            s_syms.push_back( it.first );
        //TODO fi

        for ( auto it : s_temp ){
            vector<string> seq_str_strings = it.second.get_seq_str();
            string seq_str_string = utils_unifyStrings(seq_str_strings);
            VertTirpNode s_node = VertTirpNode(seq_str_string,it.second.get_seq_length(),it.second,node);
            this->dfs_pruning(it.second,s_syms,s_node,node, avoid_same_var_states );
        }
    }
}

void VertTIRP::to_vertical(vector<vector<TI>> const &list_of_ti_seqs, vector<string> const &list_of_seqs) {
    /*
    Constructs the vertical database representation.
    For each frequent item there are an sidlist representation of that item, which is stored in the
    self.vertical_db

    :param list_of_ti_seqs: a list of time intervals of all sequences
    :param list_of_seqs: a list of sequence names
    :param time_mode:  1- timestamp mode, 2- datetime mode 3- number mode(e.g. number of frame)
    :return:
    */
    unsigned eid = 0;
    list<string>::const_iterator seqs_it;
    //list<list<TI>>::const_iterator ti_seqs_it = list_of_ti_seqs.begin();
    map<string,VertTirpSidList>::iterator sym_it;
    for (int i = 0; i < list_of_ti_seqs.size() ; i++ ){
        this->events_per_sequence.insert(make_pair(list_of_seqs[i],list_of_ti_seqs[i].size()));
        for (auto its: list_of_ti_seqs[i]) {
            // duration constraints
            time_type duration = its.get_end() - its.get_start();
            if (duration >= this->min_duration && duration <= this->max_duration) {
                sym_it = this->vertical_db.find(its.get_sym());
                if (sym_it == this->vertical_db.end())
                    sym_it = this->vertical_db.insert(pair<string, VertTirpSidList>(its.get_sym(),VertTirpSidList())).first;    //Adds the VertTirpSidList to the map
                sym_it->second.append_item(its, list_of_seqs[i], eid);

                eid++;
            }
        }
        eid = 0;
    }

    // calculate the absolute support based on number of sequences
    int n_sequences = list_of_seqs.size();
    this->min_sup = ceil(this->min_sup_rel*n_sequences);
    if ( this->min_sup == 0 )
        this->min_sup = 1;

    // save a set of frequent 1-sized items sorted lexicographically
    for ( auto db_pos = this->vertical_db.begin() ; db_pos != this->vertical_db.end() ; db_pos++ ){
        unsigned aux = db_pos->second.get_support();
        if ( db_pos->second.get_support() >= this->min_sup ){
            db_pos->second.set_n_sequences(n_sequences);
            this->f1.push_back(db_pos->first);
        }
        else
            this->vertical_db.erase(db_pos->first);
    }


    sort(this->f1.begin(),this->f1.end());
}



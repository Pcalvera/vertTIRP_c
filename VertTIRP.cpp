//
// Created by pauca on 30/03/2022.
//

#include "VertTIRP.h"
#include <cmath>

VertTIRP::VertTIRP(int time_mode, string out_file, float min_sup_rel, float eps, int min_gap, long long max_gap,
                   int min_duration, long long max_duration, bool dummy_calc, string ps, bool trans, int min_confidence ,int max_length, int min_length) {

    this->out_file = out_file;
    events_per_sequence = map<string,int>();
    this->min_sup_rel = min_sup_rel;
    this->min_confidence = min_confidence;  //todo passar parametre
    this->min_gap = min_gap;
    this->max_gap = max_gap;
    this->min_duration = min_duration;
    this->max_duration = max_duration;
    this->max_length = max_length;
    this->min_length = min_length;
    this->eps = eps;

    tirp_count = 0;
    min_sup = 0;

    this->f1 = list<string>(); //TODO
    //this->vertical_db = dict(); TODO
    //this->tree = VertTirpNode() TODO
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

int VertTIRP::mine_patterns(list<list<TI>> &list_of_ti_seqs, list<string> &list_of_seqs, bool avoid_same_var_states) {
    if ( list_of_ti_seqs.size() != list_of_seqs.size() ) throw invalid_argument("list_of_ti_seqs and list_of_seqs must have the same size");

    this->to_vertical(list_of_ti_seqs,list_of_seqs);
    //TODO taula procs

    for ( int i = 0 ; i < this->f1.size() ; i++){
        this->dfs_pruning();  //TODO fer pruning
    }
    return this->tirp_count;
}

void VertTIRP::print_patterns(bool b) {
    cout<<"Patrons printed"<<endl;
}

bool VertTIRP::same_variable(string s1, string s2, bool avoid_same_var_states) {
    return avoid_same_var_states && s1 == s2;
}

void VertTIRP::dfs_pruning() {

}

void VertTIRP::to_vertical(list<list<TI>> &list_of_ti_seqs, list<string> &list_of_seqs) {
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
    list<string>::iterator seqs_it;
    list<list<TI>>::iterator ti_seqs_it = list_of_ti_seqs.begin();
    for (seqs_it = list_of_seqs.begin() ; seqs_it != list_of_seqs.end() ; seqs_it++ ){
        this->events_per_sequence.insert(pair<string,int>(*seqs_it,(*ti_seqs_it).size()));
        for ( auto its : *ti_seqs_it){
            // duration constraints
            if ( its.get_end()-its.get_start() >= this->min_duration &&  its.get_end()-its.get_start() <= this->max_duration ){  //TODO condicio if
                if ( ! ){

                }
                eid++;
            }
        }
        eid = 0;
        ti_seqs_it++;
    }
    //TODO for
    int n_sequences = list_of_seqs.size();
    this->min_sup = ceil(this->min_sup_rel*n_sequences);

}



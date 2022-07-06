//
// Created by pauca on 10/04/2022.
//

#include "TIRPstatistics.h"

TIRPstatistics::TIRPstatistics() {
    // USEFUL TO LOCALIZE A TIRP IN THE sidlist array in a faster manner
    // a dict where key is a sequence id
    // and value is a dict where key is event id and value is a TIRP array
    this->sequence_events_tirps_dict = map<string,map<unsigned,vector<TIRP>>>();

    // vertical support, i.e. number of sequences having the pattern p
    this->sum_ver_supp = 0;

    // horizontal support per sequence, i.e. sum of all instances that have p in sequence s1
    this->sum_hor_per_seq = map<string,unsigned>();

    // MEAN DURATION VARS
    // last sequence where the TIRP appears
    // necessary to know when we changed the sequence
    this->last_modified = EMPTY;
    // a vector of sums of mean durations of sequences
    this->sum_mean_duration = vector<long long>();
    // a vector of number of instances by sequence
    this->n_instances_per_seq = vector<unsigned>();
    this->mean_duration = vector<long long>();
}

unsigned TIRPstatistics::append_tirp(string seq_id, unsigned int eid, TIRP &tirp) {
    /*
    Appends a tirp, and
    modifies sum_ver_supp, sum_hor_per_seq, and the duration variables
    :param seq_id: sequence id
    :param eid: event id
    :param tirp: tirp to add
    :return: Appends a tirp
    */
    auto it = this->sequence_events_tirps_dict.find(seq_id);
    if ( it != this->sequence_events_tirps_dict.end() ){
        auto it2 = it->second.find(eid);
        if ( it2 == it->second.end() )
            it2 = it->second.insert(pair<unsigned,vector<TIRP>>(eid,vector<TIRP>())).first;

        it2->second.push_back(tirp);
        this->sum_mean_duration.back() += tirp.get_duration();
        this->n_instances_per_seq.back() += 1;
    }
    else{
        // if self.last_modified != -1:  # change of sequence
        //      we can calculate the mean duration of the previous one
        //      self.mean_duration.append(self.sum_mean_duration[-1]/self.n_instances_per_seq[-1])

        this->sum_mean_duration.push_back(tirp.get_duration());
        this->n_instances_per_seq.push_back(1);

        //TODO no se segur si aixo funcionara
        this->sequence_events_tirps_dict[seq_id][eid] = vector<TIRP>(1,tirp);
        this->sum_ver_supp += 1;

        // initialize hor support for sequence
        this->sum_hor_per_seq[seq_id] = 0;
    }

    this->last_modified = seq_id;
    this->sum_hor_per_seq[seq_id] += 1;
    return this->sum_ver_supp;
}

float TIRPstatistics::get_sum_ver_supp() const {
    return this->sum_ver_supp;
}

float TIRPstatistics::get_mean_hor_support(map<string, unsigned int> &events_per_sequence) const {
    /*
    :param events_per_sequence: a dictionary where key is a sequence id and value is number of items in sequence
    returns the horizontal support that is self.sum_hor_per_seq / self.sum_ver_supp
    :return: returns the horizontal support that is self.sum_hor_per_seq / self.sum_ver_supp
    */
    float rel_sum = 0;
    for ( auto it : this->sum_hor_per_seq )
        rel_sum += it.second/events_per_sequence[it.first];

    return rel_sum/this->sum_ver_supp;
}

float TIRPstatistics::get_ver_support(unsigned n_sequences) const {
    /*
    returns the vertical relative support
    :param n_sequences: total number of sequences
    :return: returns the vertical relative support
    */
    return this->sum_ver_supp / n_sequences;
}

vector<long long> TIRPstatistics::get_mean_duration() {
    /*
    Returns the mean duration vector, where each event id represents a sequence
    :return: returns the mean duration vector, where each event id represents a sequence
    */
    // append the last mean_duration that have not been added yet
    if ( this->last_modified != EMPTY){
        auto n_inst = this->n_instances_per_seq.begin();
        for ( auto sum : this->sum_mean_duration ){
            // we can calculate the mean duration of the previous one
            this->mean_duration.push_back(sum/(*n_inst));
            n_inst++;
        }
        return this->mean_duration;
    }
    else // empty sequence
        return vector<long long>(1,0);
}

string TIRPstatistics::get_mean_of_means_duration(unsigned units) {
    /*
    returns the overall mean
    :param: units: 0-seconds, 1-minutes, 2-hours, 3-days, 4-weeks, 5-years
    :return: returns the overall mean
    */
    vector<long long> l = this->get_mean_duration();
    //auto j = (aux/l.size())/switcher[units]);
    return to_string(utils_mean(l)/UNITS_NUMBER[units]) + " " + UNITS_STRING[units];
}

map<string, map<unsigned, vector<TIRP>>> TIRPstatistics::get_sequence_events_tirps_dict() {
    return this->sequence_events_tirps_dict;
}

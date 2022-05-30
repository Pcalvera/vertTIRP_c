//
// Created by pauca on 30/03/2022.
//

#include "Allen.h"

Allen::Allen() {
    this->dummy_calc = true;
    this->trans = true;
    this->eps = 0;
    this->supClass = Allen_relationsEPS();
}
Allen::Allen(bool dummy_calc, bool trans, float eps, string calc_sort, Allen_relationsEPS supClass) {
    this->dummy_calc = dummy_calc;
    this->trans = trans;
    this->eps = eps;
    this->supClass = supClass;   //TODO treure subClass de arguments?
    if ( !dummy_calc ) {
        this->calc_sort = calc_sort;
        pair<PairingStrategy,list<string>> aux_pair = this->supClass.get_pairing_strategy(this->calc_sort);
        this->rels_arr = aux_pair.first;
        this->gr_arr = aux_pair.second;

        this->sorted_trans_table = map<string,Relation>();

        if ( this->eps > 0 ){
            for ( auto &it : this->supClass.trans_table ){
                if ( it.second.size() == 1){
                    this->sorted_trans_table.insert(pair<string,Relation>(it.first,Relation(it.second)));
                }
                else {
                    this->sorted_trans_table.insert(pair<string,Relation>(it.first,Relation( supClass.get_pairing_strategy(sort_rels(it.second)) )));
                }
            }
        }
        else{
            for ( auto &it : this->supClass.trans_table_0 ){
                if ( it.second.size() == 1){
                    this->sorted_trans_table.insert(pair<string,string>(it.first,it.second));
                }
                else {
                    this->sorted_trans_table.insert(pair<string,Relation>(it.first,Relation(supClass.get_pairing_strategy(sort_rels(it.second)))));
                }
            }
        }

    }
}

string Allen::sort_rels(string reducted_group) {
    string reducted_group_sorted = "";
    for ( char ch : this->calc_sort ){
        if ( reducted_group.find(ch) != string::npos  ){
            reducted_group_sorted += ch;
        }
    }
    //return reducted_group_sorted;  //TODO algoritme original retorna reducted_group
    return reducted_group;  //TODO algoritme original retorna reducted_group
}

Relation Allen::get_possible_rels(char a, char b) const{
    if ( this->dummy_calc ) {
        if ( this->eps > 0 ){
            auto it = this->supClass.trans_table.find(to_string(a) + to_string(b));
            if ( it == this->supClass.trans_table.end() ) throw(""); //TODO missatge error
            return it->second;
        }
        else{
            auto it = this->supClass.trans_table_0.find(to_string(a) + to_string(b));
            if ( it == this->supClass.trans_table_0.end() ) throw(""); //TODO missatge error
            return it->second;
        }
    }
    else {
        auto it = this->sorted_trans_table.find(to_string(a) + to_string(b));
        if ( it == this->sorted_trans_table.end() ) throw(""); //TODO missatge error
        return it->second;
    }
}

pair<string, int>
Allen::calc_rel(TI a, TI b, float eps, long long int min_gap, long long int max_gap, PairingStrategy rels_arr, list<string> gr_arr) {
    if (rels_arr.empty()){
        rels_arr = this->rels_arr;
        gr_arr = this->gr_arr;
    }

    // if b is less than a
    if ( b.get_start() < a.get_start() || ( b.get_start()==a.get_start() && b.get_end()<a.get_end() ) )
        return pair<string,int>("1",1);

    //TODO for

    return pair<string,int>("1",1);
}


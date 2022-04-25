//
// Created by pauca on 30/03/2022.
//

#include "Allen_relationsEPS.cpp"

Allen_relationsEPS::Allen::Allen() {
    this->dummy_calc = true;
    this->trans = true;
    this->eps = 0;
}
Allen_relationsEPS::Allen::Allen(bool dummy_calc, bool trans, float eps, string calc_sort, Allen_relationsEPS supClass) {
    this->dummy_calc = dummy_calc;
    this->trans = trans;
    this->eps = eps;
    if ( !dummy_calc ) {
        this->calc_sort = calc_sort;
        pair<PairingStrategy,list<string>> aux_pair = get_pairing_strategy(this->calc_sort);
        this->rels_arr = aux_pair.first;
        this->gr_arr = aux_pair.second;

        this->sorted_trans_table = map<string,Relation>();

        if ( this->eps > 0 ){
            for ( auto &it : supClass.trans_table ){
                if ( it.second.size() == 1){
                    this->sorted_trans_table.insert(pair<string,Relation>(it.first,Relation(it.second)));
                }
                else {
                    this->sorted_trans_table.insert(pair<string,Relation>(it.first,Relation( supClass.get_pairing_strategy(sort_rels(it.second)) )));
                }
            }
        }
        else{
            for ( auto &it : supClass.trans_table_0 ){
                if ( it.second.size() == 1){
                    this->sorted_trans_table.insert(pair<string,string>(it.first,it.second));
                }
                else {
                    this->sorted_trans_table.insert(pair<string,Relation>(it.first,Relation(sort_rels(it.second))));
                }
            }
        }

        //TODO acabar def
    }
}

string Allen_relationsEPS::Allen::sort_rels(string reducted_group) {
    string reducted_group_sorted = "";
    for ( char ch : this->calc_sort ){
        if ( reducted_group.find(ch) != string::npos  ){
            reducted_group_sorted += ch;
        }
    }
    return reducted_group_sorted;  //TODO algoritme original retorna reducted_group
}

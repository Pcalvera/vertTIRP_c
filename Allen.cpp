//
// Created by pauca on 30/03/2022.
//

#include "Allen.h"

Allen::Allen() {
    this->dummy_calc = true;
    this->trans = true;
    this->eps = 0;
}
Allen::Allen(bool dummy_calc, bool trans, float eps, string calc_sort) {
    this->dummy_calc = dummy_calc;
    this->trans = trans;
    this->eps = eps;
    if ( !dummy_calc ) {
        this->calc_sort = calc_sort;
        pair<PairingStrategy,list<string>> aux_pair = Allen_relationsEPS.get_pairing_strategy(this->calc_sort);
        this->rels_arr = aux_pair.first;
        this->gr_arr = aux_pair.second;

        //this->sorted_trans_table = map    TODO fer

        if ( this->eps > 0 ){

        }
        else{

        }

        //TODO acabar def
    }
}

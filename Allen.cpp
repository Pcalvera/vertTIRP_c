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
    if ( dummy_calc ) {
        this->calc_sort = calc_sort;
        //TODO acabar def
    }
}

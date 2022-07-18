//
// Created by pauca on 30/03/2022.
//

#include "Allen.h"

#include <utility>

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
        this->calc_sort = std::move(calc_sort);
        pair<PairingStrategy,vector<string>> aux_pair = Allen_relationsEPS::get_pairing_strategy(this->calc_sort);
        this->rels_arr = aux_pair.first;
        this->gr_arr = aux_pair.second;

        this->sorted_trans_table = map<string,Relation>();

        if ( this->eps > 0 ){
            for ( auto &it : Allen_relationsEPS::trans_table ){
                if ( it.second.size() == 1){
                    this->sorted_trans_table.insert(pair<string,Relation>(it.first,Relation(it.second)));
                }
                else {
                    this->sorted_trans_table.insert(pair<string,Relation>(it.first,Relation( Allen_relationsEPS::get_pairing_strategy(sort_rels(it.second)) )));
                }
            }
        }
        else{
            for ( auto &it : Allen_relationsEPS::trans_table_0 ){
                if ( it.second.size() == 1){
                    this->sorted_trans_table.insert(pair<string,string>(it.first,it.second));
                }
                else {
                    this->sorted_trans_table.insert(pair<string,Relation>(it.first,Relation(Allen_relationsEPS::get_pairing_strategy(sort_rels(it.second)))));
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
        if ( this->eps > 0 )
            return Allen_relationsEPS::trans_table.at(string({a,b}));
        else
            return Allen_relationsEPS::trans_table_0.at(string({a,b}));
    }
    else
        return this->sorted_trans_table.at(string({a,b}));

}

pair<char, int>
Allen::calc_rel(const TI &a,const TI &b, float eps, long long int min_gap, long long int max_gap, PairingStrategy rels_arr, vector<string> gr_arr)const {
    // if b is less than a
    if ( b.get_start() < a.get_start() || ( b.get_start()==a.get_start() && b.get_end()<a.get_end() ) )
        return make_pair('1',1);

    if ( this->dummy_calc ){
        pair<char,int> final_rel = make_pair('1',1);
        for ( char r : {'l','f','s','o','b','c','m','e'} ){
            pair<char,int> rel = Allen_relationsEPS::rel_func_dict.at(r)(a,b,eps,min_gap,max_gap);
            if ( rel.second != -2)
                final_rel = rel;
        }

        return final_rel;
    }
    else {
        if (rels_arr.empty()){
            rels_arr = this->rels_arr;
            gr_arr = this->gr_arr;
        }

        unsigned i = 0;
        pair<char,int> rel;
        for ( const auto &sentence : rels_arr.get_ps() ){
            if ( gr_arr[i] != NONE ){
                if ( Allen_relationsEPS::cond_dict.at(gr_arr[i])(a,b,eps,min_gap,max_gap) ){
                    for ( const Node &words : sentence ){
                        if ( words.dif == 1 ){
                            for ( const char &w : words.l ){
                                rel = Allen_relationsEPS::ind_func_dict.at(w)(a,b,eps,min_gap,max_gap);
                                if ( rel.second > -2 )
                                    return rel;
                            }
                        }
                        else{
                            rel = Allen_relationsEPS::ind_func_dict.at(words.cont)(a,b,eps,min_gap,max_gap);
                            if ( rel.second > -2 )
                                return rel;
                        }
                    }
                }
            }
            else{
                rel = Allen_relationsEPS::ind_func_dict.at('b')(a,b,eps,min_gap,max_gap);
                if ( rel.second > -2)
                    return rel;
            }
            i++;
        }

        return make_pair('1',1);
    }

}

pair<char, int>
Allen::assign_rel(const TI &a, const TI &b, const Relation &possible_rels, float eps, long long int min_gap, long long int max_gap) const {
    //TODO comentaris
    if ( this->dummy_calc ) {
        if ( !possible_rels.isString() )
            throw(""); //TODO missatge throw
        if ( possible_rels.size() == 1){  //TODO aquest if es el mateix codi que en el !dummy
            char first_r = possible_rels.getString().front();
            if ( first_r == 'b' ){ // Special case with gap
                pair<char,int> calculated = Allen_relationsEPS::ind_func_dict.at('b')(a,b,eps,min_gap,max_gap);

                if ( calculated.second != -2)
                    return calculated;
                return this->calc_rel(a,b,eps,min_gap,max_gap);
            }
            else
                return make_pair(first_r,3);
        }
        else{
            for ( char r : possible_rels.getString() ){
                pair<char,int> rel_status = Allen_relationsEPS::rel_func_dict.at(r)(a,b,eps,min_gap,max_gap);
                if ( rel_status.second != -2 )
                    return rel_status;
            }
            return this->calc_rel(a, b, eps, min_gap, max_gap);
        }
    }
    else{
        // if possible_rels is a string we get one char (the first)
        if ( possible_rels.isString() ){
            char first_r = possible_rels.getString().front();
            if ( first_r == 'b' ){ // Special case with gap
                pair<char,int> calculated = Allen_relationsEPS::ind_func_dict.at('b')(a,b,eps,min_gap,max_gap);

                if ( calculated.second != -2)
                    return calculated;
                return this->calc_rel(a,b,eps,min_gap,max_gap);
            }
            else
                return make_pair(first_r,3);
        }
        else
            return this->calc_rel(a,b,eps,min_gap,max_gap, possible_rels.getPairingStrategy().first, possible_rels.getPairingStrategy().second );
    }
}

bool Allen::get_trans() const {
    return this->trans;
}


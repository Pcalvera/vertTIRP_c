#include "AllenRelationsEPS.h"

unordered_map<char,function<int*(const TI*, const TI*, eps_type, time_type, time_type)>>
AllenRelationsEPS::ind_func_dict = {
        {'b', AllenRelationsEPS::before_ind},
        {'m', AllenRelationsEPS::meets_ind},
        {'o', AllenRelationsEPS::AllenRelationsEPS::overlaps_ind},
        {'c', AllenRelationsEPS::contains_ind},
        {'f', AllenRelationsEPS::finish_by_ind},
        {'e', AllenRelationsEPS::equal_ind},
        {'s', AllenRelationsEPS::starts_ind},
        {'l', AllenRelationsEPS::left_contains_ind}
};
unordered_map<string,function<bool(const TI*, const TI*, eps_type, time_type, time_type)>>
AllenRelationsEPS::cond_dict = {
        {"sel",  AllenRelationsEPS::sel_cond},
        {"cfmo", AllenRelationsEPS::cfmo_cond},
        {"mo",   AllenRelationsEPS::mo_cond}
};
unordered_map<char,function<int*(const TI*, const TI*, eps_type, time_type, time_type)>>
AllenRelationsEPS::rel_func_dict = {
        {'b', AllenRelationsEPS::before},
        {'m', AllenRelationsEPS::meets},
        {'o', AllenRelationsEPS::overlaps},
        {'c', AllenRelationsEPS::contains},
        {'f', AllenRelationsEPS::finish_by},
        {'e', AllenRelationsEPS::equal},
        {'s', AllenRelationsEPS::starts},
        {'l', AllenRelationsEPS::left_contains}
};
unordered_map<string,Relation>
AllenRelationsEPS::trans_table_0 = {
        // before b
        {"bb", Relation("b")},
        {"bc", Relation("b")},
        {"bo", Relation("b")},
        {"bm", Relation("b")},
        {"bs", Relation("b")},
        {"bf", Relation("b")},
        {"be", Relation("b")},
        // equal e
        {"eb", Relation("b")},
        {"ec", Relation("c")},
        {"eo", Relation("o")},
        {"em", Relation("m")},
        {"es", Relation("s")},
        {"ef", Relation("f")},
        {"ee", Relation("e")},
        // contains c
        {"cb", Relation("bcfmo")},
        {"cc", Relation("c")},
        {"co", Relation("cfo")},
        {"cm", Relation("cfo")},
        {"cs", Relation("cfo")},
        {"cf", Relation("c")},
        {"ce", Relation("c")},
        // overlaps o
        {"ob", Relation("b")},
        {"oc", Relation("bcfmo")},
        {"oo", Relation("bmo")},
        {"om", Relation("b")},
        {"os", Relation("o")},
        {"of", Relation("bmo")},
        {"oe", Relation("o")},
        // meets m
        {"mb", Relation("b")},
        {"mc", Relation("b")},
        {"mo", Relation("b")},
        {"mm", Relation("b")},
        {"ms", Relation("m")},
        {"mf", Relation("b")},
        {"me", Relation("m")},
        // starts s
        {"sb", Relation("b")},
        {"sc", Relation("bcfmo")},
        {"so", Relation("bmo")},
        {"sm", Relation("b")},
        {"ss", Relation("s")},
        {"sf", Relation("bmo")},
        {"se", Relation("s")},
        // finished by
        {"fb", Relation("b")},
        {"fc", Relation("c")},
        {"fo", Relation("o")},
        {"fm", Relation("m")},
        {"fs", Relation("o")},
        {"ff", Relation("f")},
        {"fe", Relation("f")}
};
//Trans table based of the vertTIRP article
unordered_map<string,Relation>
AllenRelationsEPS::trans_table = {
        // before b
        {"bb", Relation("b")},
        {"bc", Relation("b")},
        {"bo", Relation("b")},
        {"bm", Relation("b")},
        {"bs", Relation("b")},
        {"bf", Relation("b")},
        {"be", Relation("b")},
        // contains c
        {"cb", Relation("bcfmo")},
        {"cc", Relation("c")},
        {"co", Relation("cfo")},
        {"cm", Relation("cfo")},
        {"cs", Relation("cfo")},
        {"cf", Relation("cf")},
        {"ce", Relation("cf")},
        // overlaps o
        {"ob", Relation("b")},
        {"oc", Relation("bcfmo")},
        {"oo", Relation("bmo")},
        {"om", Relation("bm")},
        {"os", Relation("mo")},
        {"of", Relation("bfmo")},
        {"oe", Relation("mo")},
        // meets m
        {"mb", Relation("b")},
        {"mc", Relation("bm")},
        {"mo", Relation("bm")},
        {"mm", Relation("bm")},
        {"ms", Relation("bm")},
        {"mf", Relation("bm")},
        {"me", Relation("bm")},
        // starts s
        {"sb", Relation("b")},
        {"sc", Relation("bcfmo")},
        {"so", Relation("bmo")},
        {"sm", Relation("bm")},
        {"ss", Relation("ms")},
        {"sf", Relation("bmo")},
        {"se", Relation("emos")},
        // finished-by fi
        {"fb", Relation("bm")},
        {"fc", Relation("cf")},
        {"fo", Relation("fmo")},
        {"fm", Relation("bmo")},
        {"fs", Relation("fmo")},
        {"ff", Relation("cfmo")},
        {"fe", Relation("cflmo")},
        // equal e
        {"eb", Relation("bm")},
        {"ec", Relation("cf")},
        {"eo", Relation("fmo")},
        {"em", Relation("bemo")},
        {"es", Relation("eos")},
        {"ef", Relation("cfm")},
        {"ee", Relation("cefo")},
        // equal l
        {"lb", Relation("bcfmo")},
        {"lc", Relation("c")},
        {"lo", Relation("cfo")},
        {"lm", Relation("cmo")},
        {"ls", Relation("celo")},
        {"lf", Relation("cf")},
        {"le", Relation("cefl")}
};

unordered_map<char,int*>
AllenRelationsEPS::predefined_rels = {
        { 'b',rel_b3 },
        { 'm',rel_m3 },
        { 'o',rel_o3 },
        { 'c',rel_c3 },
        { 'f',rel_f3 },
        { 'e',rel_e3 },
        { 's',rel_s3 },
        { 'l',rel_l3 }
};

pair< shared_ptr<PairingStrategy>,shared_ptr<vector<string>> > AllenRelationsEPS::get_pairing_strategy(string str_rels){
    shared_ptr<PairingStrategy> rels_arr = make_shared<PairingStrategy>();
    shared_ptr<vector<string>> gr_arr = make_shared<vector<string>>();

    int i = 0,j = 0,k = 0;
    char c;
    map<char,bool> added = map<char,bool>();
    bool c_in_added;
    while ( i < str_rels.size() ){
        c = str_rels.at(i);
        c_in_added = added.find(c) != added.end();
        if ( !c_in_added && c == 'b') {
            rels_arr->add(c);
            gr_arr->emplace_back(NONE);
            added[c] = true;
        }
        else if ( !c_in_added && (c=='c' || c=='f' || c=='m' || c=='o') ){
            gr_arr->emplace_back("cfmo");
            if ( c == 'm' || c == 'o' ){
                rels_arr->add2(c);
                added[c] = true;
                j = i + 1;

                k = i + 1;
                while ( k < str_rels.size() ){
                    c = str_rels.at(k);
                    c_in_added = added.find(c) != added.end();
                    if ( !c_in_added && (c == 'm' || c == 'o') ){
                        rels_arr->append2(c);
                        added[c] = true;
                    }
                    k++;
                }
                while ( j < str_rels.size() ){
                    c = str_rels.at(j);
                    c_in_added = added.find(c) != added.end();
                    if ( !c_in_added && (c == 'c' || c == 'f') ){
                        rels_arr->append(c);
                        added[c] = true;
                    }
                    j++;
                }
            }
            else{
                rels_arr->add(c);
                added[c] = true;
                j = i + 1;
                while ( j < str_rels.size() ){
                    c = str_rels.at(j);
                    c_in_added = added.find(c) != added.end();
                    if ( !c_in_added ){
                        if ( c == 'c' || c == 'f'){
                            rels_arr->append(c);
                            added[c] = true;
                        }
                        else if ( c == 'm' || c == 'o' ){
                            rels_arr->appendAdd(c);
                            added[c] = true;
                            k = j + 1;
                            while ( k < str_rels.size() ){
                                c = str_rels.at(k);
                                c_in_added = added.find(c) != added.end();
                                if ( !c_in_added && (c == 'm' || c == 'o') ){
                                    rels_arr->append2(c);
                                    added[c] = true;
                                }
                                k++;
                            }
                        }
                    }
                    j++;
                }
            }
        }
        else{
            if ( !c_in_added ) {
                rels_arr->add(c);
                added[c] = true;
                gr_arr->emplace_back("sel");
                j = i + 1;
                while (j < str_rels.size()) {
                    c = str_rels.at(j);
                    c_in_added = added.find(c) != added.end();
                    if (!c_in_added) {
                        if (c == 's' || c == 'e' || c == 'l') {
                            rels_arr->append(c);
                            added[c] = true;
                        }
                    }
                    j++;
                }
            }
        }
        i++;
    }
    return make_pair(rels_arr,gr_arr);
}

int* AllenRelationsEPS::before_ind(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap){
    dif_time_type b_s_a_e = truncate(b->get_start()-a->get_end());
    if ( b_s_a_e > eps ){
        if ( min_gap != 0 && b_s_a_e < min_gap )
            return rel_11;
        else if ( max_gap != MAXGAP && b_s_a_e > max_gap )
            return rel_22;
        else
            return rel_b3;
    }
    else
        return rel_noneMinus2;
}
int* AllenRelationsEPS::meets_ind(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap){
    dif_time_type b_s_a_e = truncate(b->get_start()-a->get_end());
    if ( abs(b_s_a_e) <= eps )
        return rel_m3;
    else
        return rel_noneMinus2;
}
int* AllenRelationsEPS::overlaps_ind(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap){
    dif_time_type b_s_a_e = truncate(b->get_start()-a->get_end());
    if ( b_s_a_e < (-eps) )
        return rel_o3;
    else
        return rel_noneMinus2;
}
int* AllenRelationsEPS::contains_ind(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap) {
    dif_time_type b_s_a_e = truncate(b->get_end() - a->get_end());
    if (b_s_a_e < (-eps))
        return rel_c3;
    else
        return rel_noneMinus2;
}
int* AllenRelationsEPS::finish_by_ind(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap){
    dif_time_type b_s_a_e = truncate(b->get_end()-a->get_end());
    if ( abs(b_s_a_e) <= eps )
        return rel_f3;
    else
        return rel_noneMinus2;
}
int* AllenRelationsEPS::equal_ind(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap){
    dif_time_type b_s_a_e = truncate(b->get_end()-a->get_end());
    if ( abs(b_s_a_e) <= eps )
        return rel_e3;
    else
        return rel_noneMinus2;
}
int* AllenRelationsEPS::starts_ind(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap){
    dif_time_type b_s_a_e = truncate(b->get_end()-a->get_end());
    if ( b_s_a_e > eps )
        return rel_s3;
    else
        return rel_noneMinus2;
}
int* AllenRelationsEPS::left_contains_ind(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap){
    if ( eps == 0 )
        return rel_none2;
    dif_time_type b_s_a_e = truncate(b->get_end()-a->get_end());
    if ( b_s_a_e < (-eps) )
        return rel_l3;
    else
        return rel_noneMinus2;
}
bool AllenRelationsEPS::sel_cond(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap){
    dif_time_type b_s_a_s = truncate(b->get_start()-a->get_start());
    return abs(b_s_a_s) <= eps;
}
bool AllenRelationsEPS::cfmo_cond(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap){
    dif_time_type b_s_a_s = truncate(b->get_start()-a->get_start());
    return b_s_a_s > eps;
}
bool AllenRelationsEPS::mo_cond(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap){
    dif_time_type b_s_a_e = truncate(b->get_end()-a->get_end());
    return b_s_a_e > eps;
}

bool AllenRelationsEPS::true_cond(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap){
    return true;
}

int* AllenRelationsEPS::before(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap) {
    return ind_func_dict.at('b')(a,b,eps,min_gap,max_gap);
}

int* AllenRelationsEPS::meets(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap) {
    if ( abs( truncate(b->get_start() - a->get_end())) <= eps && truncate(b->get_start()-a->get_start()) > eps && truncate(b->get_end() - a->get_end()) > eps )
        return rel_m3;
    else
        return rel_noneMinus2;
}

int* AllenRelationsEPS::overlaps(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap) {
    if ( truncate(b->get_start()-a->get_start()) > eps && truncate(b->get_end()-a->get_end()) > eps && truncate(a->get_end()-b->get_start()) > eps )
        return rel_o3;
    else
        return rel_noneMinus2;
}

int* AllenRelationsEPS::contains(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap) {
    if ( truncate(b->get_start() - a->get_start()) > eps && truncate(a->get_end() - b->get_end()) > eps )
        return rel_c3;
    else
        return rel_noneMinus2;
}

int* AllenRelationsEPS::finish_by(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap) {
    if ( (b->get_start() - a->get_start()) > eps && abs(b->get_end() - a->get_end()) <= eps )
        return rel_f3;
    else
        return rel_noneMinus2;}

int* AllenRelationsEPS::equal(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap) {
    if ( truncate(b->get_start() - a->get_start()) <= eps && abs(truncate(b->get_end() - a->get_end())) <= eps )
        return rel_e3;
    else
        return rel_noneMinus2;}

int* AllenRelationsEPS::starts(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap) {
    if ( abs(truncate(b->get_start() - a->get_start())) <= eps && truncate(b->get_end() - a->get_end()) > eps )
        return rel_s3;
    else
        return rel_noneMinus2;}

int* AllenRelationsEPS::left_contains(const TI* a, const TI* b, eps_type eps, time_type min_gap, time_type max_gap) {
    if ( eps > 0 && abs(truncate(b->get_start() - a->get_start())) <= eps && truncate(b->get_end() - a->get_end()) < (-eps) )
        return rel_l3;
    else
        return rel_noneMinus2;
}

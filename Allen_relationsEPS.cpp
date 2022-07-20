#include "Allen_relationsEPS.h"

map<char,function<pair<char,int>(const TI&,const TI&,float, long long, long long)>>
Allen_relationsEPS::ind_func_dict = {
        {'b', Allen_relationsEPS::before_ind},
        {'m', Allen_relationsEPS::meets_ind},
        {'o', Allen_relationsEPS::Allen_relationsEPS::overlaps_ind},
        {'c', Allen_relationsEPS::contains_ind},
        {'f', Allen_relationsEPS::finish_by_ind},
        {'e', Allen_relationsEPS::equal_ind},
        {'s', Allen_relationsEPS::starts_ind},
        {'l', Allen_relationsEPS::left_contains_ind}
};
map<string,function<bool(const TI&,const TI&,float, long long, long long)>>
Allen_relationsEPS::cond_dict = {
        {"sel", Allen_relationsEPS::sel_cond},
        {"cfmo", Allen_relationsEPS::cfmo_cond},
        {"mo", Allen_relationsEPS::mo_cond}
};
map<char,function<pair<char,int>(const TI&,const TI&,float, long long, long long)>>
Allen_relationsEPS::rel_func_dict = {
        {'b', Allen_relationsEPS::before},
        {'m', Allen_relationsEPS::meets},
        {'o', Allen_relationsEPS::overlaps},
        {'c', Allen_relationsEPS::contains},
        {'f', Allen_relationsEPS::finish_by},
        {'e', Allen_relationsEPS::equal},
        {'s', Allen_relationsEPS::starts},
        {'l', Allen_relationsEPS::left_contains}
};
map<string,string>
Allen_relationsEPS::trans_table_0 = {
        // before b
        {"bb", "b"},
        {"bc", "b"},
        {"bo", "b"},
        {"bm", "b"},
        {"bs", "b"},
        {"bf", "b"},
        {"be", "b"},
        // equal e
        {"eb", "b"},
        {"ec", "c"},
        {"eo", "o"},
        {"em", "m"},
        {"es", "s"},
        {"ef", "f"},
        {"ee", "e"},
        // contains c
        {"cb", "bcfmo"},
        {"cc", "c"},
        {"co", "cfo"},
        {"cm", "cfo"},
        {"cs", "cfo"},
        {"cf", "c"},
        {"ce", "c"},
        // overlaps o
        {"ob", "b"},
        {"oc", "bcfmo"},
        {"oo", "bmo"},
        {"om", "b"},
        {"os", "o"},
        {"of", "bmo"},
        {"oe", "o"},
        // meets m
        {"mb", "b"},
        {"mc", "b"},
        {"mo", "b"},
        {"mm", "b"},
        {"ms", "m"},
        {"mf", "b"},
        {"me", "m"},
        // starts s
        {"sb", "b"},
        {"sc", "bcfmo"},
        {"so", "bmo"},
        {"sm", "b"},
        {"ss", "s"},
        {"sf", "bmo"},
        {"se", "s"},
        // finished by
        {"fb", "b"},
        {"fc", "c"},
        {"fo", "o"},
        {"fm", "m"},
        {"fs", "o"},
        {"ff", "f"},
        {"fe", "f"}
};
//Trans table based of the vertTIRP article
map<string,string>
Allen_relationsEPS::trans_table = {
        // before b
        {"bb", "b"},
        {"bc", "b"},
        {"bo", "b"},
        {"bm", "b"},
        {"bs", "b"},
        {"bf", "b"},
        {"be", "b"},
        // contains c
        {"cb", "bcfmo"},
        {"cc", "c"},
        {"co", "cfo"},
        {"cm", "cfo"},
        {"cs", "cfo"},
        {"cf", "cf"},
        {"ce", "cf"},
        // overlaps o
        {"ob", "b"},
        {"oc", "bcfmo"},
        {"oo", "bmo"},
        {"om", "bm"},
        {"os", "mo"},
        {"of", "bfmo"},
        {"oe", "mo"},
        // meets m
        {"mb", "b"},
        {"mc", "bm"},
        {"mo", "bm"},
        {"mm", "bm"},
        {"ms", "bm"},
        {"mf", "bm"},
        {"me", "bm"},
        // starts s
        {"sb", "b"},
        {"sc", "bcfmo"},
        {"so", "bmo"},
        {"sm", "bm"},
        {"ss", "ms"},
        {"sf", "bmo"},
        {"se", "emos"},
        // finished-by fi
        {"fb", "bm"},
        {"fc", "cf"},
        {"fo", "fmo"},
        {"fm", "bmo"},
        {"fs", "fmo"},
        {"ff", "cfmo"},
        {"fe", "cflmo"},
        // equal e
        {"eb", "bm"},
        {"ec", "cf"},
        {"eo", "fmo"},
        {"em", "bemo"},
        {"es", "eos"},
        {"ef", "cfm"},
        {"ee", "cefo"},
        // equal l
        {"lb", "bcfmo"},
        {"lc", "c"},
        {"lo", "cfo"},
        {"lm", "cmo"},
        {"ls", "celo"},
        {"lf", "cf"},
        {"le", "cefl"}
};

pair<PairingStrategy,vector<string>> Allen_relationsEPS::get_pairing_strategy(string str_rels){ //TODO arreglar
    PairingStrategy rels_arr = PairingStrategy();
    vector<string> gr_arr = vector<string>();

    int i = 0,j = 0,k = 0;
    char c;
    map<char,bool> added = map<char,bool>();
    bool c_in_added;
    while ( i < str_rels.size() ){
        c = str_rels.at(i);
        c_in_added = added.find(c) != added.end();
        if ( !c_in_added && c == 'b') {   //TODO millor al reves?
            rels_arr.add(c);
            gr_arr.emplace_back(NONE);
            update_added(added,c,true);
        }
        else if ( !c_in_added && (c=='c' || c=='f' || c=='m' || c=='o') ){
            gr_arr.emplace_back("cfmo");
            if ( c == 'm' || c == 'o' ){
                rels_arr.add2(c);
                update_added(added,c,true);
                j = i + 1;

                k = i + 1;
                while ( k < str_rels.size() ){
                    c = str_rels.at(k);
                    c_in_added = added.find(c) != added.end();
                    if ( !c_in_added && (c == 'm' || c == 'o') ){
                        rels_arr.append2(c);
                        update_added(added,c,true);
                    }
                    k++;
                }
                while ( j < str_rels.size() ){
                    c = str_rels.at(j);
                    c_in_added = added.find(c) != added.end();
                    if ( !c_in_added && (c == 'c' || c == 'f') ){
                        rels_arr.append(c);
                        update_added(added,c,true);
                    }
                    j++;
                }
            }
            else{                            //TODO comprovar si funciona
                rels_arr.add(c);
                update_added(added,c,true);
                j = i + 1;
                while ( j < str_rels.size() ){
                    c = str_rels.at(j);
                    c_in_added = added.find(c) != added.end();
                    if ( !c_in_added ){
                        if ( c == 'c' || c == 'f'){
                            rels_arr.append(c);
                            update_added(added,c,true);
                        }
                        else if ( c == 'm' || c == 'o' ){
                            rels_arr.appendAdd(c);
                            update_added(added,c,true);
                            k = j + 1;
                            while ( k < str_rels.size() ){
                                c = str_rels.at(k);
                                c_in_added = added.find(c) != added.end();
                                if ( !c_in_added && (c == 'm' || c == 'o') ){
                                    rels_arr.append2(c);
                                    update_added(added,c,true);
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
                rels_arr.add(c);
                update_added(added, c, true);
                gr_arr.emplace_back("sel");
                j = i + 1;
                while (j < str_rels.size()) {
                    c = str_rels.at(j);
                    c_in_added = added.find(c) != added.end();
                    if (!c_in_added) {
                        if (c == 's' || c == 'e' || c == 'l') {
                            rels_arr.append(c);
                            update_added(added, c, true);
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

void Allen_relationsEPS::update_added(map<char,bool> &added,char c, bool b){
    auto added_it = added.insert(pair<char,bool>(c,true));
    if (!added_it.second) added_it.first->second = true;
}
pair<char,int> Allen_relationsEPS::before_ind(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_e = b.get_start()-a.get_end();
    if ( b_s_a_e > eps ){
        if ( min_gap != 0 && b_s_a_e < min_gap )
            return make_pair('1',1);
        else if ( max_gap != MAXGAP && b_s_a_e > max_gap )
            return make_pair('2',2);
        else
            return make_pair('b',3);
    }
    else
        return make_pair('\0',-2);
}
pair<char,int> Allen_relationsEPS::meets_ind(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_e = b.get_start()-a.get_end();
    if ( abs(b_s_a_e) <= eps )
        return make_pair('m',3);
    else
        return make_pair('\0',-2);
}
pair<char,int> Allen_relationsEPS::overlaps_ind(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_e = b.get_start()-a.get_end();
    if ( b_s_a_e < (-eps) )
        return make_pair('o',3);
    else
        return make_pair('\0',-2);
}
pair<char,int> Allen_relationsEPS::contains_ind(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_e = b.get_end()-a.get_end();
    if ( b_s_a_e < (-eps) )
        return make_pair('c',3);
    else
        return make_pair('\0',-2);
}
pair<char,int> Allen_relationsEPS::finish_by_ind(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_e = b.get_end()-a.get_end();
    if ( abs(b_s_a_e) <= eps )
        return make_pair('f',3);
    else
        return make_pair('\0',-2);
}
pair<char,int> Allen_relationsEPS::equal_ind(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_e = b.get_end()-a.get_end();
    if ( abs(b_s_a_e) <= eps )
        return make_pair('e',3);
    else
        return make_pair('\0',-2);
}
pair<char,int> Allen_relationsEPS::starts_ind(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_e = b.get_end()-a.get_end();
    if ( b_s_a_e > eps )
        return make_pair('s',3);
    else
        return make_pair('\0',-2);
}
pair<char,int> Allen_relationsEPS::left_contains_ind(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap){
    if ( eps == 0 )
    return make_pair('\0',2);
    long long b_s_a_e = b.get_end()-a.get_end();
    if ( b_s_a_e < (-eps) )
        return make_pair('l',3);
    else
        return make_pair('\0',-2);
}
bool Allen_relationsEPS::sel_cond(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_s = b.get_start()-a.get_start();
    return abs(b_s_a_s) <= eps;
}
bool Allen_relationsEPS::cfmo_cond(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_s = b.get_start()-a.get_start();
    return b_s_a_s > eps;
}
bool Allen_relationsEPS::mo_cond(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_e = b.get_end()-a.get_end();
    return b_s_a_e > eps;
}
bool Allen_relationsEPS::true_cond(const TI &a, const TI &b, float eps, long long min_gap, long long max_gap){
    return true;
}

pair<char, int> Allen_relationsEPS::before(const TI &a, const TI &b, float eps, long long int min_gap, long long int max_gap) {
    return ind_func_dict.at('b')(a,b,eps,min_gap,max_gap);
}

pair<char, int> Allen_relationsEPS::meets(const TI &a, const TI &b, float eps, long long int min_gap, long long int max_gap) {
    if ( abs( b.get_start() - a.get_end()) <= eps && (b.get_start()-a.get_start()) > eps && (b.get_end() - a.get_end()) > eps )
        return make_pair('m',3);
    else
        return make_pair('\0',-2);
}

pair<char, int> Allen_relationsEPS::overlaps(const TI &a, const TI &b, float eps, long long int min_gap, long long int max_gap) {
    if ( (b.get_start()-a.get_start()) > eps && (b.get_end()-a.get_end()) > eps && (a.get_end()-b.get_start()) > eps )
        return make_pair('o',3);
    else
        return make_pair('\0',-2);
}

pair<char, int> Allen_relationsEPS::contains(const TI &a, const TI &b, float eps, long long int min_gap, long long int max_gap) {
    if ( (b.get_start() - a.get_start()) > eps && (a.get_end() - b.get_end()) > eps )
        return make_pair('c',3);
    else
        return make_pair('\0',-2);
}

pair<char, int> Allen_relationsEPS::finish_by(const TI &a, const TI &b, float eps, long long int min_gap, long long int max_gap) {
    if ( (b.get_start() - a.get_start()) > eps && abs(b.get_end() - a.get_end()) <= eps )
        return make_pair('f',3);
    else
        return make_pair('\0',-2);
}

pair<char, int> Allen_relationsEPS::equal(const TI &a, const TI &b, float eps, long long int min_gap, long long int max_gap) {
    if ( ( b.get_start() - a.get_start()) <= eps && abs(b.get_end() - a.get_end()) <= eps )
        return make_pair('e',3);
    else
        return make_pair('\0',-2);
}

pair<char, int> Allen_relationsEPS::starts(const TI &a, const TI &b, float eps, long long int min_gap, long long int max_gap) {
    if ( abs(b.get_start() - a.get_start()) <= eps && (b.get_end() - a.get_end()) > eps )
        return make_pair('s',3);
    else
        return make_pair('\0',-2);
}

pair<char, int>
Allen_relationsEPS::left_contains(const TI &a, const TI &b, float eps, long long int min_gap, long long int max_gap) {
    if ( eps > 0 && abs(b.get_start() - a.get_start()) <= eps && (b.get_end() - a.get_end()) < (-eps) )
        return make_pair('l',3);
    else
        return make_pair('\0',-2);
}












































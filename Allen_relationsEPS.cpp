#include "Allen_relationsEPS.h"

Allen_relationsEPS::Allen_relationsEPS(){
    trans_table_0 = {
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
    trans_table = {
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
    ind_func_dict = {
            {"b", before_ind},
            {"m", meets_ind},
            {"o", overlaps_ind},
            {"c", contains_ind},
            {"f", finish_by_ind},
            {"e", equal_ind},
            {"s", starts_ind},
            {"l", left_contains_ind}
    };
    cond_dict = {
            {"sel", sel_cond},
            {"cfmo", cfmo_cond},
            {"mo", mo_cond}
    };
}

pair<PairingStrategy,list<string>> Allen_relationsEPS::get_pairing_strategy(string str_rels){
    PairingStrategy rels_arr = PairingStrategy();
    list<string> gr_arr = list<string>();

    int i = 0,j = 0,k = 0;
    char c;
    map<char,bool> added = map<char,bool>();
    bool c_in_added;
    while ( i < str_rels.size() ){
        c = str_rels.at(i);
        c_in_added = added.find(c) != added.end();
        if ( !c_in_added && c == 'b') {   //TODO millor al reves?
            rels_arr.add(c);
            gr_arr.push_back(NONE);
            update_added(added,c,true);
        }
        else if ( !c_in_added && (c=='c' || c=='f' || c=='m' || c=='o') ){
            gr_arr.push_back("cfmo");
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
                gr_arr.push_back("sel");
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
    return pair<PairingStrategy,list<string>>(rels_arr,gr_arr);
}

void Allen_relationsEPS::update_added(map<char,bool> &added,char c, bool b){
    auto added_it = added.insert(pair<char,bool>(c,true));
    if (!added_it.second) added_it.first->second = true;
}
//TODO canviar els return pair per return make_pair
pair<string,int> Allen_relationsEPS::before_ind(TI a, TI b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_e = b.get_start()-a.get_end();
    if ( b_s_a_e > eps ){
        if ( min_gap != 0 && b_s_a_e < min_gap )
            return pair<string,int>("1",1);
        else if ( max_gap != MAXGAP && b_s_a_e > max_gap )
            return pair<string,int>("2",2);
        else
            return pair<string,int>("b",3);
    }
    else
        return pair<string,int>("-2",-2);
}
pair<string,int> Allen_relationsEPS::meets_ind(TI a, TI b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_e = b.get_start()-a.get_end();
    if ( abs(b_s_a_e) <= eps )
        return pair<string,int>("m",3);
    else
        return pair<string,int>("-2",-2);
}
pair<string,int> Allen_relationsEPS::overlaps_ind(TI a, TI b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_e = b.get_start()-a.get_end();
    if ( b_s_a_e < (-eps) )
        return pair<string,int>("o",3);
    else
        return pair<string,int>("-2",-2);
}
pair<string,int> Allen_relationsEPS::contains_ind(TI a, TI b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_e = b.get_end()-a.get_end();
    if ( b_s_a_e < (-eps) )
        return pair<string,int>("c",3);
    else
        return pair<string,int>("-2",-2);
}
pair<string,int> Allen_relationsEPS::finish_by_ind(TI a, TI b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_e = b.get_end()-a.get_end();
    if ( abs(b_s_a_e) <= eps )
        return pair<string,int>("f",3);
    else
        return pair<string,int>("-2",-2);
}
pair<string,int> Allen_relationsEPS::equal_ind(TI a, TI b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_e = b.get_end()-a.get_end();
    if ( abs(b_s_a_e) <= eps )
        return pair<string,int>("e",3);
    else
        return pair<string,int>("-2",-2);
}
pair<string,int> Allen_relationsEPS::starts_ind(TI a, TI b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_e = b.get_end()-a.get_end();
    if ( b_s_a_e > eps )
        return pair<string,int>("s",3);
    else
        return pair<string,int>("-2",-2);
}
pair<string,int> Allen_relationsEPS::left_contains_ind(TI a, TI b, float eps, long long min_gap, long long max_gap){
    if ( eps == 0 )
    return pair<string,int>("-2",2);
    long long b_s_a_e = b.get_end()-a.get_end();
    if ( b_s_a_e < (-eps) )
        return pair<string,int>("l",3);
    else
        return pair<string,int>("-2",-2);
}
bool Allen_relationsEPS::sel_cond(TI a, TI b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_s = b.get_start()-a.get_start();
    return abs(b_s_a_s) <= eps;
}
bool Allen_relationsEPS::cfmo_cond(TI a, TI b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_s = b.get_start()-a.get_start();
    return b_s_a_s > eps;
}
bool Allen_relationsEPS::mo_cond(TI a, TI b, float eps, long long min_gap, long long max_gap){
    long long b_s_a_e = b.get_end()-a.get_end();
    return b_s_a_e > eps;
}
bool Allen_relationsEPS::true_cond(TI a, TI b, float eps, long long min_gap, long long max_gap){
    return true;
}












































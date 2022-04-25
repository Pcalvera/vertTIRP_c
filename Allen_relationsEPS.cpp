#include <iostream>
#include <cstdlib>
#include "map"
#include "list"
#include "TI.h"
#include "PairingStrategy.h"
#include "Relation.h"

using namespace std;

const long long MAXGAP = 3155695200;
const string NONE = "N";

class Allen_relationsEPS{
public:
    Allen_relationsEPS(){
        // before b
        trans_table_0.insert(pair<string,string>("bb","b"));
        trans_table_0.insert(pair<string,string>("bc","b"));
        trans_table_0.insert(pair<string,string>("bo","b"));
        trans_table_0.insert(pair<string,string>("bm","b"));
        trans_table_0.insert(pair<string,string>("bs","b"));
        trans_table_0.insert(pair<string,string>("bf","b"));
        trans_table_0.insert(pair<string,string>("be","b"));

        // equal e
        trans_table_0.insert(pair<string,string>("eb","b"));
        trans_table_0.insert(pair<string,string>("ec","c"));
        trans_table_0.insert(pair<string,string>("eo","o"));
        trans_table_0.insert(pair<string,string>("em","m"));
        trans_table_0.insert(pair<string,string>("es","s"));
        trans_table_0.insert(pair<string,string>("ef","f"));
        trans_table_0.insert(pair<string,string>("ee","e"));

        // contains c
        trans_table_0.insert(pair<string,string>("cb","bcfmo"));
        trans_table_0.insert(pair<string,string>("cc","c"));
        trans_table_0.insert(pair<string,string>("co","cfo"));
        trans_table_0.insert(pair<string,string>("cm","cfo"));
        trans_table_0.insert(pair<string,string>("cs","cfo"));
        trans_table_0.insert(pair<string,string>("cf","c"));
        trans_table_0.insert(pair<string,string>("ce","c"));

        // overlaps o
        trans_table_0.insert(pair<string,string>("ob","b"));
        trans_table_0.insert(pair<string,string>("oc","bcfmo"));
        trans_table_0.insert(pair<string,string>("oo","bmo"));
        trans_table_0.insert(pair<string,string>("om","b"));
        trans_table_0.insert(pair<string,string>("os","o"));
        trans_table_0.insert(pair<string,string>("of","bmo"));
        trans_table_0.insert(pair<string,string>("oe","o"));

        // meets m
        trans_table_0.insert(pair<string,string>("mb","b"));
        trans_table_0.insert(pair<string,string>("mc","b"));
        trans_table_0.insert(pair<string,string>("mo","b"));
        trans_table_0.insert(pair<string,string>("mm","b"));
        trans_table_0.insert(pair<string,string>("ms","m"));
        trans_table_0.insert(pair<string,string>("mf","b"));
        trans_table_0.insert(pair<string,string>("me","m"));

        // starts s
        trans_table_0.insert(pair<string,string>("sb","b"));
        trans_table_0.insert(pair<string,string>("sc","bcfmo"));
        trans_table_0.insert(pair<string,string>("so","bmo"));
        trans_table_0.insert(pair<string,string>("sm","b"));
        trans_table_0.insert(pair<string,string>("ss","s"));
        trans_table_0.insert(pair<string,string>("sf","bmo"));
        trans_table_0.insert(pair<string,string>("se","s"));

        // finished by
        trans_table_0.insert(pair<string,string>("fb","b"));
        trans_table_0.insert(pair<string,string>("fc","c"));
        trans_table_0.insert(pair<string,string>("fo","o"));
        trans_table_0.insert(pair<string,string>("fm","m"));
        trans_table_0.insert(pair<string,string>("fs","o"));
        trans_table_0.insert(pair<string,string>("ff","f"));
        trans_table_0.insert(pair<string,string>("fe","f"));

        //Trans table based of the vertTIRP article

        // before b
        trans_table.insert(pair<string,string>("bb","b"));
        trans_table.insert(pair<string,string>("bc","b"));
        trans_table.insert(pair<string,string>("bo","b"));
        trans_table.insert(pair<string,string>("bm","b"));
        trans_table.insert(pair<string,string>("bs","b"));
        trans_table.insert(pair<string,string>("bf","b"));
        trans_table.insert(pair<string,string>("be","b"));

        // contains c
        trans_table.insert(pair<string,string>("cb","bcfmo"));
        trans_table.insert(pair<string,string>("cc","c"));
        trans_table.insert(pair<string,string>("co","cfo"));
        trans_table.insert(pair<string,string>("cm","cfo"));
        trans_table.insert(pair<string,string>("cs","cfo"));
        trans_table.insert(pair<string,string>("cf","cf"));
        trans_table.insert(pair<string,string>("ce","cf"));

        // overlaps o
        trans_table.insert(pair<string,string>("ob","b"));
        trans_table.insert(pair<string,string>("oc","bcfmo"));
        trans_table.insert(pair<string,string>("oo","bmo"));
        trans_table.insert(pair<string,string>("om","bm"));
        trans_table.insert(pair<string,string>("os","mo"));
        trans_table.insert(pair<string,string>("of","bfmo"));
        trans_table.insert(pair<string,string>("oe","mo"));

        // meets m
        trans_table.insert(pair<string,string>("mb","b"));
        trans_table.insert(pair<string,string>("mc","bm"));
        trans_table.insert(pair<string,string>("mo","bm"));
        trans_table.insert(pair<string,string>("mm","bm"));
        trans_table.insert(pair<string,string>("ms","bm"));
        trans_table.insert(pair<string,string>("mf","bm"));
        trans_table.insert(pair<string,string>("me","bm"));

        // starts s
        trans_table.insert(pair<string,string>("sb","b"));
        trans_table.insert(pair<string,string>("sc","bcfmo"));
        trans_table.insert(pair<string,string>("so","bmo"));
        trans_table.insert(pair<string,string>("sm","bm"));
        trans_table.insert(pair<string,string>("ss","ms"));
        trans_table.insert(pair<string,string>("sf","bmo"));
        trans_table.insert(pair<string,string>("se","emos"));

        // finished-by fi
        trans_table.insert(pair<string,string>("fb","bm"));
        trans_table.insert(pair<string,string>("fc","cf"));
        trans_table.insert(pair<string,string>("fo","fmo"));
        trans_table.insert(pair<string,string>("fm","bmo"));
        trans_table.insert(pair<string,string>("fs","fmo"));
        trans_table.insert(pair<string,string>("ff","cfmo"));
        trans_table.insert(pair<string,string>("fe","cflmo"));

        // equal e
        trans_table.insert(pair<string,string>("eb","bm"));
        trans_table.insert(pair<string,string>("ec","cf"));
        trans_table.insert(pair<string,string>("eo","fmo"));
        trans_table.insert(pair<string,string>("em","bemo"));
        trans_table.insert(pair<string,string>("es","eos"));
        trans_table.insert(pair<string,string>("ef","cfm"));
        trans_table.insert(pair<string,string>("ee","cefo"));

        // equal l
        trans_table.insert(pair<string,string>("lb","bcfmo"));
        trans_table.insert(pair<string,string>("lc","c"));
        trans_table.insert(pair<string,string>("lo","cfo"));
        trans_table.insert(pair<string,string>("lm","cmo"));
        trans_table.insert(pair<string,string>("ls","celo"));
        trans_table.insert(pair<string,string>("lf","cf"));
        trans_table.insert(pair<string,string>("le","cefl"));
    }

    static pair<PairingStrategy,list<string>> get_pairing_strategy(string str_rels){
        PairingStrategy rels_arr = PairingStrategy();
        list<string> gr_arr = list<string>();

        int i,j,k = 0;
        char c;
        map<char,bool> added = map<char,bool>();
        bool c_in_added;
        while ( i < str_rels.size() ){
            c = str_rels.at(i);
            c_in_added = added.find(c) == added.end();
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
                        c_in_added = added.find(c) == added.end();
                        if ( !c_in_added && (c == 'm' || c == 'o') ){
                            rels_arr.append2(c);
                            update_added(added,c,true);
                        }
                        k++;
                    }
                    while ( j < str_rels.size() ){
                        c = str_rels.at(j);
                        c_in_added = added.find(c) == added.end();
                        if ( !c_in_added && (c == 'c' || c == 'f') ){
                            rels_arr.append(c);
                            update_added(added,c,true);
                        }
                        j++;
                    }
                }
                else{

                }
            }
            else{
                rels_arr.add(c);
                update_added(added,c,true);
                gr_arr.push_back("sel");
                j = i+1;
                while ( j < str_rels.size() ){
                    c = str_rels.at(j);
                    c_in_added = added.find(c) == added.end();
                    if ( !c_in_added ){
                        if ( c == 's' || c == 'e' || c == 'l' ){
                            rels_arr.append(c);
                            update_added(added,c,true);
                        }
                    }
                    j ++;
                }
            }
            i++;
        }
        return pair<PairingStrategy,list<string>>(rels_arr,gr_arr);
    }
    static void update_added(map<char,bool> &added,char c, bool b){
        auto added_it = added.insert(pair<char,bool>(c,true));
        if (!added_it.second) added_it.first->second = true;
    }

    static pair<string,int> before_ind(TI a, TI b, float eps, long long min_gap, long long max_gap){
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
    static pair<string,int> meets_ind(TI a, TI b, float eps, long long min_gap, long long max_gap){
        long long b_s_a_e = b.get_start()-a.get_end();
        if ( abs(b_s_a_e) <= eps )
            return pair<string,int>("m",3);
        else
            return pair<string,int>("-2",-2);
    }
    static pair<string,int> overlaps_ind(TI a, TI b, float eps, long long min_gap, long long max_gap){
        long long b_s_a_e = b.get_start()-a.get_end();
        if ( b_s_a_e < (-eps) )
            return pair<string,int>("o",3);
        else
            return pair<string,int>("-2",-2);

    }
    static pair<string,int> contains_ind(TI a, TI b, float eps, long long min_gap, long long max_gap){
        long long b_s_a_e = b.get_end()-a.get_end();
        if ( b_s_a_e < (-eps) )
            return pair<string,int>("c",3);
        else
            return pair<string,int>("-2",-2);
    }
    static pair<string,int> finish_by_ind(TI a, TI b, float eps, long long min_gap, long long max_gap){
        long long b_s_a_e = b.get_end()-a.get_end();
        if ( abs(b_s_a_e) <= eps )
            return pair<string,int>("f",3);
        else
            return pair<string,int>("-2",-2);
    }
    static pair<string,int> equal_ind(TI a, TI b, float eps, long long min_gap, long long max_gap){
        long long b_s_a_e = b.get_end()-a.get_end();
        if ( abs(b_s_a_e) <= eps )
            return pair<string,int>("e",3);
        else
            return pair<string,int>("-2",-2);
    }
    static pair<string,int> starts_ind(TI a, TI b, float eps, long long min_gap, long long max_gap){
        long long b_s_a_e = b.get_end()-a.get_end();
        if ( b_s_a_e > eps )
            return pair<string,int>("s",3);
        else
            return pair<string,int>("-2",-2);
    }
    static pair<string,int> left_contains_ind(TI a, TI b, float eps, long long min_gap, long long max_gap){
        if ( eps == 0 )
        return pair<string,int>("-2",2);
        long long b_s_a_e = b.get_end()-a.get_end();
        if ( b_s_a_e < (-eps) )
            return pair<string,int>("l",3);
        else
            return pair<string,int>("-2",-2);
    }
    static bool sel_cond(TI a, TI b, float eps, long long min_gap, long long max_gap){
        long long b_s_a_s = b.get_start()-a.get_start();
        return abs(b_s_a_s) <= eps;
    }
    static bool cfmo_cond(TI a, TI b, float eps, long long min_gap, long long max_gap){
        long long b_s_a_s = b.get_start()-a.get_start();
        return b_s_a_s > eps;
    }
    static bool mo_cond(TI a, TI b, float eps, long long min_gap, long long max_gap){
        long long b_s_a_e = b.get_end()-a.get_end();
        return b_s_a_e > eps;
    }
    static bool true_cond(TI a, TI b, float eps, long long min_gap, long long max_gap){
        return true;
    }

    // Trans table based on Mantaining Knowledge about Temporal Intervals
    // by James F.Allen
    map<string,string> trans_table_0;
    //Trans table based of the vertTIRP article
    map<string,string> trans_table;
    //TODO mapes amb funcions

    class Allen {
        public:
            Allen();
            Allen(bool dummy_calc, bool trans = true, float eps = 0, string calc_sort="bselfmoc", Allen_relationsEPS supClass = Allen_relationsEPS() );
            string sort_rels(string reducted_group);

        private:
            string calc_sort;
            bool dummy_calc;
            bool trans;
            float eps;

            //For non dummy
            PairingStrategy rels_arr;
            list<string> gr_arr;
            map<string,Relation> sorted_trans_table;
    };
};







































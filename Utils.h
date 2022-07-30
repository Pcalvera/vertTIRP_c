//
// Created by pauca on 21/07/2022.
//

#ifndef VERTTIRP_C_UTILS_H
#define VERTTIRP_C_UTILS_H

#include <fstream>
#include <sstream>
#include <ctime>
#include <numeric>
#include "TI.h"
#include "list"
#include "vector"
#include "map"

using namespace std;


struct ReadTi {
    vector<vector<TI>> list_of_ti_users = vector<vector<TI>>();
    vector<string> list_of_users = vector<string>();
    int ti_count = 0;
};
struct Csv_df {
    //map<string,vector<string>> csv_df;
    vector<vector<string>> content;
    vector<string> header;
    int getIndex(string s){
        for ( int  i = 0 ; i < header.size() ; i++ ){
            if ( header.at(i) == s ) return i;
        }
        return -1;
    }
    vector<int> getValIndex(vector<string> s){
        vector<int> res;
        for ( int  i = 0 ; i < header.size() ; i++ ){
            for ( const string& aux : s ){
                if ( aux == header.at(i) ){
                    res.push_back(i);
                    break;
                }
            }
        }
        return res;
    }
    map<string,vector<TI>> groupbyUid(){
        map<string,vector<TI>> aux = map<string,vector<TI>>();
        return aux;
    }
};

Csv_df utils_csvRead(string &filename);
ReadTi utils_tiRead(string &filepath, char sep, string &seqid_column, string &date_column_name_start, string &date_column_name_end, string &date_format, vector<string> &val_column_names,
                    bool is_null_f= true, int time_mode= 1);
TI utils_stringsToTi(string data_inici,string data_fi,string val);
tm utils_splitDate(const string &s);
long long utils_mean(vector<time_type> &l);
string utils_unifyStrings(vector<string> &seq_str_strings);
string utils_unifyStrings2(vector<string> &seq_str_strings);
string utils_unifyChars (string &seq_chars );
template <typename T,typename V> vector<T> utils_getKeys(map<T,V> m);


#endif //VERTTIRP_C_UTILS_H

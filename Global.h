//
// Created by pauca on 31/05/2022.
//

#ifndef VERTTIRP_C_GLOBAL_H
#define VERTTIRP_C_GLOBAL_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <bits/stdc++.h>
#include "TI.h"
#include "list"
#include "vector"
#include "map"

typedef float support_type;
typedef float eps_type;
typedef long long gap_type;
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
    map<string,vector<TI>> groupbyUid(){
        map<string,vector<TI>> aux = map<string,vector<TI>>();
        return aux;
    }
};

Csv_df utils_csvRead(string &filename);
ReadTi utils_tiRead(string &filepath, char sep, string &seqid_column, string &date_column_name_start, string &date_column_name_end, string &date_format, vector<string> &val_column_names,
               bool is_null_f=true, int time_mode=1);
TI utils_vectToTi(vector<string> &v);
tm utils_splitDate(string &s);
long long utils_mean(vector<long long> &l);
string utils_unifyStrings(vector<string> &seq_str_strings);
string utils_unifyChars (string &seq_chars );
template <typename T,typename V> vector<T> utils_getKeys(map<T,V> m);

#endif //VERTTIRP_C_GLOBAL_H

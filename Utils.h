//
// Created by pauca on 31/05/2022.
//

#ifndef VERTTIRP_C_UTILS_H
#define VERTTIRP_C_UTILS_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "TI.h"
#include "list"
#include "vector"
#include "map"

using namespace std;


struct ReadTi {
    list<list<TI>> list_of_ti_users = list<list<TI>>();
    list<string> list_of_users = list<string>();
    int ti_count = 0;
};
struct Csv_df {
    //map<string,vector<string>> csv_df;
    vector<vector<string>> content;
    vector<string> header;
    map<string,list<TI>> groupbyUid(){
        map<string,list<TI>> aux = map<string,list<TI>>();
        return aux;
    }
};

Csv_df utils_csvRead(string &filename);
ReadTi utils_tiRead(string &filepath, char sep, string &seqid_column, string &date_column_name_start, string &date_column_name_end, string &date_format, vector<string> &val_column_names,
               bool is_null_f=true, int time_mode=1);
TI utils_vectToTi(vector<string> &v);
tm utils_splitDate(string &s);
long long utils_mean(vector<long long> &l);
template <typename T,typename V> vector<T> get_keys(map<T,V> m);

#endif //VERTTIRP_C_UTILS_H

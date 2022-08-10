//
// Created by pauca on 21/07/2022.
//

#ifndef VERTTIRP_C_UTILS_H
#define VERTTIRP_C_UTILS_H

#include <fstream>
#include <sstream>
#include <ctime>
#include <numeric>
#include <memory>
#include <algorithm>
#include "TI.h"
#include "list"
#include "vector"
#include "map"

using namespace std;

struct Csv_line {
    string start_time;
    string end_time;
    vector<string> values;
};
struct Ti_node {
    Ti_node(shared_ptr<TI> &ti);
    shared_ptr<TI> ti;
    shared_ptr<Ti_node> next;
    shared_ptr<Ti_node> ant;
};

class LinkedList {
public:
    LinkedList();
    //~LinkedList();

    bool empty();
    int getSize() const;

    void setFirst();
    void next();
    shared_ptr<TI>& getActual();
    bool isLast();

    void insert(const TI &ti);
    void sortedInsert(shared_ptr<Ti_node> new_node, shared_ptr<Ti_node> last_inserted = nullptr);
    //void free();
private:

    shared_ptr<Ti_node> first;
    shared_ptr<Ti_node> last;
    shared_ptr<Ti_node> actual;
    int size;
};

map<string,vector<Csv_line>> read_csv(string &filename,string &seq_h,string &start_h, string &end_h, vector<string> &values);
LinkedList ti_to_list(const vector<Csv_line> &df, string &date_column_name_start, string &date_column_name_end, vector<string> &val_column_names ,bool timemode_number = true);
pair<vector<string>,vector<LinkedList>> utils_tiRead(string &filepath, char sep, string &seqid_column, string &date_column_name_start, string &date_column_name_end, string &date_format, vector<string> &val_column_names,
                    bool is_null_f= true, bool timemode_number = true);
TI utils_stringsToTi(string data_inici,string data_fi,string val,bool timemode_number);
tm utils_splitDate(const string &s);
long long utils_mean(vector<time_type> &l);
string utils_unifyStrings(vector<string> &seq_str_strings);
string utils_unifyStrings2(vector<string> &seq_str_strings);
string utils_unifyChars (string &seq_chars );


template <typename T,typename V> vector<T> utils_getKeys(map<T,V> m);

#endif //VERTTIRP_C_UTILS_H

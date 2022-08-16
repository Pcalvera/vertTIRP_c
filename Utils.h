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
    Ti_node(TI *ti);
    ~Ti_node();
    TI *ti;
    Ti_node *next;
    Ti_node *ant;
};

class LinkedList {
public:
    LinkedList();
    LinkedList(const LinkedList &o);
    ~LinkedList();

    bool empty();
    int getSize() const;

    void setFirst();
    void next();
    TI* getActual();
    bool isLast();

    LinkedList& operator=(const LinkedList &o);

    void insert(TI *ti);
    void sortedInsert(Ti_node* new_node, Ti_node* last_inserted);
    //void printPointerCount();
    void free();
    void copy(const LinkedList &o);
private:

    Ti_node *first;
    Ti_node *last;
    Ti_node *actual;
    int size;
};

void read_csv(string &filename,string &seq_h,string &start_h, string &end_h, vector<string> &values, map<string,vector<Csv_line>> &content );
void ti_to_list(const vector<Csv_line> &df, string &date_column_name_start, string &date_column_name_end, vector<string> &val_column_names ,bool timemode_number, LinkedList &list_of_ti);
void utils_tiRead(string &filepath, char sep, string &seqid_column, string &date_column_name_start, string &date_column_name_end, string &date_format, vector<string> &val_column_names, vector<string> &ret_list_of_sequences,vector<LinkedList> &ret_list_of_ti_sequences, bool timemode_number = true);
TI utils_stringsToTi(string data_inici,string data_fi,string val,bool timemode_number);
tm utils_splitDate(const string &s);
long long utils_mean(vector<time_type> &l);
string utils_unifyStrings(vector<string> &seq_str_strings);
string utils_unifyStrings2(vector<string> &seq_str_strings);
string utils_unifyChars (string &seq_chars );

#endif //VERTTIRP_C_UTILS_H

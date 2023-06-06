//
// Created by pauca on 21/07/2022.
//

#include "Utils.h"

#include <memory>

Ti_node::Ti_node(TI* ti){
    this->ti = ti;
    this->ant = nullptr;
    this->next = nullptr;
}

Ti_node::~Ti_node() {
    delete this->ti;
}

void read_csv(string &filename,string &seq_h,string &start_h, string &end_h, vector<string> &values, map<string,vector<Csv_line>> &content ) {
    string line, word;
    int seq_index,start_index,end_index;
    vector<string> row;
    vector<int> values_index = vector<int>();

    ifstream file;
    file.open(filename);
    if (file.is_open()) {
        if (getline(file, line)) {
            line.erase(std::remove(line.begin(), line.end(), '\r' ), line.end()); //Erase \n and \r from windows and unix formats
            line.erase(std::remove(line.begin(), line.end(), '\n' ), line.end());
            row.clear();
            stringstream str(line);
            int i = 0;
            while (getline(str, word, ';')) {
                if ( word == seq_h )
                    seq_index =  i;
                else if ( word == start_h )
                    start_index = i;
                else if ( word == end_h )
                    end_index = i;
                else{
                    for ( auto &s : values){
                        if ( s == word ){
                            values_index.push_back(i);
                            break;
                        }
                    }
                }
                i++;
            }

            while (getline(file, line)) {
                line.erase(std::remove(line.begin(), line.end(), '\r' ), line.end()); //Erase \n and \r from windows and unix formats
                line.erase(std::remove(line.begin(), line.end(), '\n' ), line.end());
                row.clear();
                stringstream str2(line);
                while (getline(str2, word, ';'))
                    row.push_back(word);
                if ( row.size() != i )
                    throw("File read invalid line");
                Csv_line cl;
                cl.start_time = row[start_index];
                cl.end_time = row[end_index];
                cl.values = vector<string>();
                for ( int j : values_index)
                    cl.values.push_back(row[j]);
                content[row[seq_index]].push_back(cl);
            }
        }
    } else
        throw("Could not open the file\n");
}
void ti_to_list(const vector<Csv_line> &df, string &date_column_name_start, string &date_column_name_end, vector<string> &val_column_names,int timemode, LinkedList &list_of_ti){
    if ( df.size() < 2 )
        return;

    time_type startTime;
    time_type endTime;

    Ti_node *current_node = nullptr;
    Ti_node *last_node;
    for ( int i = 0 ; i < val_column_names.size() ; i++ ){
        string attr_name = val_column_names[i] + "_";
        last_node = nullptr;
        for ( const Csv_line &line : df ) {
            if (timemode == 1) {  //timestramp
                tm start = utils_splitDate(line.start_time);
                tm finish = utils_splitDate(line.end_time);
                startTime = mktime(&start);
                endTime = mktime(&finish);
            }
            else if (timemode == 2) {
                startTime = stoll(line.start_time)*0.000000001;
                endTime = stoll(line.end_time)*0.000000001;
            }
            else if ( timemode == 3){
                startTime = stoll(line.start_time);
                endTime = stoll(line.end_time);
            }
            TI *ti = new TI(attr_name + line.values[i], startTime, endTime);
            current_node = new Ti_node(ti);
            list_of_ti.sortedInsert(current_node, last_node);
            last_node = current_node;
        }
    }
}
void utils_tiRead(string &filepath, char sep, string &seqid_column, string &date_column_name_start,
                    string &date_column_name_end, string &date_format, vector<string> &val_column_names, vector<string> &ret_list_of_sequences,vector<LinkedList> &ret_list_of_ti_sequences, int timemode) {
    map<string,vector<Csv_line>> df = map<string,vector<Csv_line>>();
    read_csv(filepath,seqid_column,date_column_name_start,date_column_name_end,val_column_names,df);
    ret_list_of_sequences.reserve(df.size()+1);
    ret_list_of_ti_sequences.reserve(df.size()+1);
    LinkedList ti;
    for ( auto const &item : df ){
        ti = LinkedList();
        ti_to_list(item.second, date_column_name_start, date_column_name_end, val_column_names,
                   timemode,ti);
        if (!ti.empty()) {
            ret_list_of_sequences.push_back(item.first);
            ret_list_of_ti_sequences.emplace_back(ti);
        }
    }
}

tm utils_splitDate(const string &s) {
    string date = s.substr(0, s.find(" "));
    string hourMinute = s.substr(s.find(" ") + 1);
    unsigned long long first = date.find("/");
    unsigned long long second = date.find("/", first + 1);
    string date1 = date.substr(0, first);
    string date2 = date.substr(first + 1, second - first - 1);
    string date3 = date.substr(second + 1);
    unsigned long long third = hourMinute.find(":");
    string hour1 = hourMinute.substr(0, third);
    string hour2 = hourMinute.substr(third + 1);

    tm t = tm();
    t.tm_min = stoi(hour2);
    t.tm_hour = stoi(hour1);
    t.tm_mday = stoi(date2);
    t.tm_mon = stoi(date1) - 1;
    t.tm_year = stoi(date3) - 1900;
    return t;
}

long long utils_mean(vector<time_type> &l) {
    long long sum = 0;
    for (const time_type &i: l)
        sum += i;
    return sum / (unsigned) l.size();
}

string utils_unifyStrings(vector<string> &seq_str_strings){
    return "['" + accumulate(seq_str_strings.begin(),seq_str_strings.end(),string(""),[](string &ss, string &s)
    {
        return ss.empty() ? s : ss + "', '" + s;
    }) + "']";
}
string utils_unifyChars (string &seq_chars ){
    if ( seq_chars.empty() ) return "[' ']";
    return "['" + accumulate(seq_chars.begin(),seq_chars.end(),string(""),[](string ss, char &s)
    {
        return ss.empty() ? string(1,s) : ss + "', '" + s;
    }) + "']";
}

dif_time_type truncate(dif_time_type t) {
    //if ( t < 1e-6) return 0;
    return t;
}

LinkedList::LinkedList() {
    this->first = this->last = this->actual = nullptr;
    this->size = 0;
}

LinkedList::LinkedList(const LinkedList &o) {
    this->first = this->last = this->actual = nullptr;
    this->size = 0;
    this->copy(o);
}

LinkedList::~LinkedList() {
    free();
}

bool LinkedList::empty() {
    return this->first == nullptr;
}

int LinkedList::getSize() const {
    return this->size;
}

LinkedList &LinkedList::operator=(const LinkedList &o) {
    if (this != &o) {
        this->free();
        this->copy(o);
    }
    return(*this);
}

void LinkedList::insert(TI *ti) {
    auto * newNode = new Ti_node(ti);
    Ti_node * antNode;
    if (actual == NULL) {
        antNode = last;
        last = newNode;
    } else {
        antNode = actual->ant;
        actual->next = newNode;
    }
    newNode->next = actual;
    if (antNode == NULL)
        first = newNode;
    else
        antNode->next = newNode;
    newNode->ant = antNode;
    this->size++;
}

void LinkedList::sortedInsert(Ti_node *new_node, Ti_node *last_inserted ) {
    if ( this->first == nullptr ){
        this->first = new_node;
        this->last = new_node;
        new_node->next = nullptr;
        new_node->ant = nullptr;
    }
    else if ( *new_node->ti < *this->first->ti ){
        new_node->next = this->first;
        this->first->ant = new_node;
        this->first = new_node;
    }
    else{
        Ti_node *present;
        if ( last_inserted != nullptr && last_inserted->ant != nullptr)
            present = last_inserted->ant;
        else
            present = this->first;

        while ( present->next != nullptr && *present->next->ti < *new_node->ti )
            present = present->next;

        new_node->next = present->next;
        if ( new_node->next == nullptr )
            this->last = new_node;
        else
            present->next->ant = new_node;

        present->next = new_node;
        new_node->ant = present;
    }
    this->size++;
}

void LinkedList::setFirst() {
    this->actual = first;
}

void LinkedList::next() {
    if ( isLast() )
        throw("Iterator pointer out of range");
    actual = actual->next;
}

TI* LinkedList::getActual() {
    if ( this->actual == nullptr)
        throw("Iterator pointer is null");
    return this->actual->ti;
}

bool LinkedList::isLast() {
    return actual == nullptr;
}

void LinkedList::free() {
    while ( this->first != nullptr ){
        Ti_node *p = this->first;
        this->first = this->first->next;
        delete p;
    }
    this->size = 0;
}

void LinkedList::copy(const LinkedList &o) {
    Ti_node * p = o.first;
    while ( p != nullptr ){
        TI *newTi = new TI(*p->ti);
        insert(newTi);
        p = p->next;
    }
}


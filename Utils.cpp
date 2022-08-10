//
// Created by pauca on 21/07/2022.
//

#include "Utils.h"

#include <memory>

Ti_node::Ti_node(shared_ptr<TI> &ti){
    this->ti = ti;
    this->ant = nullptr;
    this->next = nullptr;
}

map<string,vector<Csv_line>> read_csv(string &filename,string &seq_h,string &start_h, string &end_h, vector<string> &values) {
    map<string,vector<Csv_line>> content = map<string,vector<Csv_line>>();
    string line, word;
    int seq_index,start_index,end_index;
    vector<string> row;
    vector<int> values_index = vector<int>();

    ifstream file;
    file.open(filename);
    if (file.is_open()) {
        if (getline(file, line)) {
            row.clear(); //TODO
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
                row.clear();  //TODO
                stringstream str(line);
                while (getline(str, word, ';'))
                    row.push_back(word);
                if ( row.size() != i )
                    throw(""); //TODO
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
    return content;
}
LinkedList ti_to_list(const vector<Csv_line> &df, string &date_column_name_start, string &date_column_name_end, vector<string> &val_column_names,bool timemode_number){
    //vector<TI> list_of_ti = vector<TI>();
    LinkedList list_of_ti = LinkedList();
    if ( df.size() < 2 )
        return list_of_ti;
        //return list_of_ti;

    time_type startTime;
    time_type endTime;

    shared_ptr<Ti_node> current_node = nullptr;
    shared_ptr<Ti_node> last_node;
    for ( int i = 0 ; i < val_column_names.size() ; i++ ){
        string attr_name = val_column_names[i] + "_";
        last_node = nullptr;
        for ( const Csv_line &line : df ) {
            if ( timemode_number ){
                startTime = stoll(line.start_time); //*0.000000001
                endTime = stoll(line.end_time); //*0.000000001
            }
            else { //timestramp
                tm start = utils_splitDate(line.start_time);
                tm finish = utils_splitDate(line.end_time);
                startTime = mktime(&start);
                endTime = mktime(&finish);
            }
            shared_ptr<TI> ti = make_shared<TI>(attr_name + line.values[i], startTime, endTime);
            current_node = std::make_shared<Ti_node>(ti); //TODO hauria de ser new?
            //list_of_ti.push_back(ti);
            if ( list_of_ti.getSize() == 21 || ti->get_sym() == "Passive_Arm_N" && ti->get_start() == 3582 && ti->get_end() == 3633 )
                int djskflfj = 3;
            //cout<<list_of_ti.getSize()<<": "<<((last_node != nullptr)? last_node->ti.get_sym() : "null") <<endl;
            list_of_ti.sortedInsert(current_node, last_node);
            last_node = current_node;
        }
    }
    //std::sort(list_of_ti.begin(), list_of_ti.end());
    return list_of_ti;

}
pair<vector<string>,vector<LinkedList>> utils_tiRead(string &filepath, char sep, string &seqid_column, string &date_column_name_start,
                    string &date_column_name_end, string &date_format, vector<string> &val_column_names,
                    bool is_null_f, bool timemode_number) {
    //TODO is_null
    map<string,vector<Csv_line>> df = read_csv(filepath,seqid_column,date_column_name_start,date_column_name_end,val_column_names);
    vector<LinkedList> list_of_ti_sequences = vector<LinkedList>();
    vector<string> list_of_sequences = vector<string>();

    LinkedList ti = LinkedList();
    for ( auto const &item : df ){
        ti = ti_to_list(item.second, date_column_name_start, date_column_name_end, val_column_names,
                        timemode_number);
        if (!ti.empty()) {
            list_of_sequences.push_back(item.first);
            list_of_ti_sequences.push_back(ti);
        }
    }
    return make_pair(list_of_sequences,list_of_ti_sequences);
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
string utils_unifyStrings2(vector<string> &seq_str_strings){
    return accumulate(seq_str_strings.begin(),seq_str_strings.end(),string(""),[](string &ss, string &s)
    {
        return ss.empty() ? s : ss + "_" + s;
    });
}
string utils_unifyChars (string &seq_chars ){
    if ( seq_chars.empty() ) return "[' ']";
    return "['" + accumulate(seq_chars.begin(),seq_chars.end(),string(""),[](string ss, char &s)
    {
        return ss.empty() ? string(1,s) : ss + "', '" + s;
    }) + "']";
}

template<typename T, typename V>
vector<T> utils_getKkeys(map<T, V> m) {
    vector<T> res =  vector<T>();
    for ( const auto &it : m)
        res.push_back( it.first );
    return res;
}

LinkedList::LinkedList() {
    this->first = this->last = this->actual = nullptr;
    this->size = 0;
}

//LinkedList::~LinkedList() {
//    free();
//}

bool LinkedList::empty() {
    return this->first == nullptr;
}

int LinkedList::getSize() const {
    return this->size;
}

void LinkedList::insert(const TI &ti) {

}

void LinkedList::sortedInsert(shared_ptr<Ti_node> new_node, shared_ptr<Ti_node> last_inserted ) {
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
        shared_ptr<Ti_node> present;
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

shared_ptr<TI>& LinkedList::getActual() {
    if ( this->actual == nullptr)
        throw("Iterator pointer is null");
    return this->actual->ti;
}

bool LinkedList::isLast() {
    return actual == nullptr;
}

//void LinkedList::free() {
//    while ( this->first != nullptr ){
//        Ti_node *p = this->first;
//        this->first = this->first->next;
//        delete p;
//    }
//    this->size = 0;
//}


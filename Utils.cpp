//
// Created by pauca on 21/07/2022.
//

#include "Utils.h"

Csv_df utils_csvRead(string &filename) {
    Csv_df result;
    vector<vector<string>> content;
    vector<string> header = vector<string>();
    vector<string> row;
    string line, word;

    ifstream file;
    file.open(filename);
    if (file.is_open()) {
        if (getline(file, line)) {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ';'))
                header.push_back(word);

            while (getline(file, line)) {
                row.clear();
                stringstream str(line);
                while (getline(str, word, ';'))
                    row.push_back(word);
                content.push_back(row);
            }
            result.content = content;
            result.header = header;
        }
    } else
        cout << "Could not open the file\n";

    return result;
}

ReadTi utils_tiRead(string &filepath, char sep, string &seqid_column, string &date_column_name_start,
                    string &date_column_name_end, string &date_format, vector<string> &val_column_names,
                    bool is_null_f, int time_mode) {
    //TODO is_null
    ReadTi result;
    Csv_df df = utils_csvRead(filepath);
    map<string, vector<TI>> grouped_by_uid = df.groupbyUid();

    for (const auto &i: df.content) {
        //TI ti = TI(i[3].at(0),1,2);
        TI ti = utils_vectToTi(i);

        if (grouped_by_uid.count(i[0]) == 0) {
            vector<TI> aux = vector<TI>();
            aux.push_back(ti);
            grouped_by_uid.insert(pair<string, vector<TI>>(i[0], aux));
        } else {
            auto it = grouped_by_uid.find(i[0]);
            it->second.push_back(ti);
        }
        result.ti_count++;
    }
    for (const auto &j: grouped_by_uid) {
        result.list_of_users.push_back(j.first);
        result.list_of_ti_users.push_back(j.second);
    }

    return result;
}

TI utils_vectToTi(const vector<string> &v) {
    tm start = utils_splitDate(v[1]);
    tm finish = utils_splitDate(v[2]);
    string value = "value_";
    return TI(value + v[3].at(0), mktime(&start), mktime(&finish));
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
    for (const long long &i: l)
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

template<typename T, typename V>
vector<T> utils_getKkeys(map<T, V> m) {
    vector<T> res =  vector<T>();
    for ( const auto &it : m)
        res.push_back( it.first );
    return res;
}
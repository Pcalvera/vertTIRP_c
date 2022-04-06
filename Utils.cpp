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
    int ti_count;
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
class Utils {
public:
    static Csv_df csv_read(string filename){
        Csv_df result;
        vector<vector<string>> content;
        vector<string> header = vector<string>();
        vector<string> row;
        string line, word;

        ifstream file;
        file.open(filename );
        if(file.is_open())
        {
            if ( getline(file, line) ) {
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
        }
        else
            cout<<"Could not open the file\n";

        return result;
    }

    static ReadTi ti_read(string filepath, char sep, string seqid_column, string date_column_name_start, string date_column_name_end, string date_format, vector<string> val_column_names,
                   bool is_null_f=true, int time_mode=1){
        //TODO is_null
        ReadTi result;
        result.ti_count = 0;
        Csv_df df = csv_read(filepath);
        map<string,list<TI>> grouped_by_uid = df.groupbyUid();

        for (auto & i : df.content) {
            //TI ti = TI(i[3].at(0),1,2);
            TI ti = vect_to_ti(i); //TODO tractar date_format

            if ( grouped_by_uid.count(i[0]) == 0 ) {
                list<TI> aux = list<TI>();
                aux.push_back(ti);
                grouped_by_uid.insert(pair<string,list<TI>>(i[0],aux));
            }
            else {
                auto it = grouped_by_uid.find(i[0]);
                it->second.push_back(ti);
            }
            result.ti_count++;
        }
        for( auto & j : grouped_by_uid ){
            result.list_of_users.push_back(j.first);
            result.list_of_ti_users.push_back(j.second);
        }

        return result;
    }

    static TI vect_to_ti(vector<string> v){
        tm start = splitDate(v[1]);
        tm finish = splitDate(v[2]);
        string value = "value_";
        return TI(value+v[3].at(0),mktime(&start),mktime(&finish));
    }

    static tm splitDate(string s){
        string date = s.substr(0, s.find(" "));
        string hourMinute = s.substr( s.find(" ")+1);
        unsigned long long first = date.find("/");
        unsigned long long second = date.find("/",first+1);
        string date1 = date.substr(0, first );
        string date2 = date.substr(first+1, second-first-1 );
        string date3 = date.substr(second+1 );
        unsigned long long third = hourMinute.find(":");
        string hour1 = hourMinute.substr(0,third);
        string hour2 = hourMinute.substr(third+1);

        tm t = tm();
        t.tm_min = stoi(hour2);
        t.tm_hour = stoi(hour1);
        t.tm_mday = stoi(date2);
        t.tm_mon = stoi(date1)-1;
        t.tm_year = stoi(date3)-1900;
        return t;
    }
};

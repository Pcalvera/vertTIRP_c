#include <iostream>
#include <fstream>
#include <sstream>
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
    int suma(int a){
        return a;
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
                //for ( int i = 0 ; i < header.size() ; i++ ){
                //    //result.csv_df.insert(pair<string,vector<string>>(header[i],content[i]));
                //}
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
        Csv_df df = csv_read(filepath);

        return result;
    }
};

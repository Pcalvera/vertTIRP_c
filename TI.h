//
// Created by pauca on 31/03/2022.
//

#ifndef VERTTIRP_C_TI_H
#define VERTTIRP_C_TI_H
#include <iostream>
#include "Global.cpp"

using namespace std;

class TI {
public:
    TI(string sym, time_type start, time_type end);
    time_type get_start()const;
    time_type get_end()const;
    string get_sym()const;

    friend ostream &operator<<(ostream &os, const TI &ti);
    bool operator==(const TI &rhs) const;
    bool operator!=(const TI &rhs) const;

    bool operator<(const TI &rhs) const;

    bool operator>(const TI &rhs) const;

    bool operator<=(const TI &rhs) const;

    bool operator>=(const TI &rhs) const;

private:
    string sym;
    time_type start;
    time_type end;
};


#endif //VERTTIRP_C_TI_H

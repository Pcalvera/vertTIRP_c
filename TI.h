//
// Created by pauca on 31/03/2022.
//

#ifndef VERTTIRP_C_TI_H
#define VERTTIRP_C_TI_H
#include <iostream>
using namespace std;

class TI {
public:
    TI(string sym, long long start, long long end);
    long long get_start();
    long long get_end();
    string get_sym();

    friend ostream &operator<<(ostream &os, const TI &ti);
    bool operator==(const TI &rhs) const;
    bool operator!=(const TI &rhs) const;

    bool operator<(const TI &rhs) const;

    bool operator>(const TI &rhs) const;

    bool operator<=(const TI &rhs) const;

    bool operator>=(const TI &rhs) const;

private:
    string sym;
    long long start;
    long long end;
};


#endif //VERTTIRP_C_TI_H

//
// Created by pauca on 31/03/2022.
//

#ifndef VERTTIRP_C_TI_H
#define VERTTIRP_C_TI_H
#include <iostream>
using namespace std;

class TI {
public:
    TI(char sym, float start, float end);
    friend ostream &operator<<(ostream &os, const TI &ti);
    bool operator==(const TI &rhs) const;
    bool operator!=(const TI &rhs) const;

    bool operator<(const TI &rhs) const;

    bool operator>(const TI &rhs) const;

    bool operator<=(const TI &rhs) const;

    bool operator>=(const TI &rhs) const;

private:
    char sym;
    float start;
    float end;
};


#endif //VERTTIRP_C_TI_H

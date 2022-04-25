//
// Created by pauca on 21/04/2022.
//

#ifndef VERTTIRP_C_RELATION_H
#define VERTTIRP_C_RELATION_H
#include <iostream>
#include "PairingStrategy.h"

using namespace std;

class Relation {
public:
    Relation(string s);
    Relation(PairingStrategy p);
    bool isString()const;
    char getString()const;
    PairingStrategy getPairingStrategy()const;
private:
    bool isS; //True if contains a char, false if contaings a PairingStrategy
    char s;
    PairingStrategy p;
};


#endif //VERTTIRP_C_RELATION_H

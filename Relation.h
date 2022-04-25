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
    Relation(pair<PairingStrategy,list<string>> p);
    bool isString()const;
    string getString()const;
    pair<PairingStrategy,list<string>> getPairingStrategy()const;
private:
    bool isS; //True if contains a char, false if contaings a PairingStrategy
    string s;
    pair<PairingStrategy,list<string>> p;
};


#endif //VERTTIRP_C_RELATION_H

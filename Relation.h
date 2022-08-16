//
// Created by pauca on 21/04/2022.
//

#ifndef VERTTIRP_C_RELATION_H
#define VERTTIRP_C_RELATION_H
#include <iostream>
#include <memory>
#include "PairingStrategy.h"
#include "list"

using namespace std;

class Relation {
public:
    Relation(string s);
    Relation(pair< shared_ptr<PairingStrategy>,shared_ptr<vector<string>> > p);
    bool isString()const;
    string getString()const;
    pair< shared_ptr<PairingStrategy>,shared_ptr<vector<string>> >& getPairingStrategy();
    unsigned size()const;
private:
    bool isS; //True if contains a char, false if contaings a PairingStrategy
    string s;
    pair< shared_ptr<PairingStrategy>,shared_ptr<vector<string>> > p;
};


#endif //VERTTIRP_C_RELATION_H

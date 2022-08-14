//
// Created by pauca on 21/04/2022.
//

#include "Relation.h"

Relation::Relation(string s) {
    this->s = s;
    this->isS = true;
}
Relation::Relation(pair<PairingStrategy,vector<string>> p) {
    this->p = p;
    this->isS = false;
}

bool Relation::isString() const {
    return this->isS;
}

//Pre: this->isS == true
string Relation::getString() const {
    return this->s;
}
//Pre: this->isS == false
pair<PairingStrategy,vector<string>> Relation::getPairingStrategy() const {
    return this->p;   //TODO retornar ref?
}

unsigned Relation::size() const {
    if ( !isS )
        return p.second.size();
    else
        return s.size();
}

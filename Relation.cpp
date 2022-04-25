//
// Created by pauca on 21/04/2022.
//

#include "Relation.h"

Relation::Relation(string s) {
    this->s = s;
    this->isS = true;
}
Relation::Relation(pair<PairingStrategy,list<string>> p) {
    this->p = p;
    this->isS = false;
}

bool Relation::isString() const {
    return this->isS;
}

//Pre: this->isS == true
string Relation::getString() const {
    //TODO comprovar? if ( !isString() ) throw("");
    return this->s;
}
//Pre: this->isS == false
pair<PairingStrategy,list<string>> Relation::getPairingStrategy() const {
    //TODO comprovar? if ( isString() ) throw("");
    return this->p;
}

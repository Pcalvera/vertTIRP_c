//
// Created by pauca on 21/04/2022.
//

#include "Relation.h"

Relation::Relation(string s) {
    this->s = s;
    this->isS = true;
}
Relation::Relation(PairingStrategy p) {
    this->p = p;
    this->isS = false;
}

bool Relation::isString() const {
    return this->isS;
}

//Pre: this->isC == true
char Relation::getString() const {
    //TODO comprovar? if ( !isString() ) throw("");
    return this->s;
}
//Pre: this->isC == false
PairingStrategy Relation::getPairingStrategy() const {
    //TODO comprovar? if ( isString() ) throw("");
    return this->p;
}

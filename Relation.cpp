//

#include "Relation.h"

Relation::Relation(string s) {
    this->s = s;
    this->isS = true;
}
Relation::Relation(pair< shared_ptr<PairingStrategy>,shared_ptr<vector<string>> > p) {
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
pair< shared_ptr<PairingStrategy>,shared_ptr<vector<string>> >& Relation::getPairingStrategy()  {
    return this->p;
}

unsigned Relation::size() const {
    if ( !isS )
        return p.second->size();
    else
        return s.size();
}

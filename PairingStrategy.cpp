//
// Created by pauca on 10/04/2022.
//

#include "PairingStrategy.h"


PairingStrategy::PairingStrategy(int size) {
    // pre: -
    // post: l’arbre és buit
    if ( size < 2 ) throw(""); //TODO missatge d'error
    arrel = NULL;
    last_sub1 = NULL;
    last_sub2 = NULL;
    this->size = size;
}

PairingStrategy::~PairingStrategy(){
    // pre: cert
    // post: allibera la memòria reservada per l’arbre
    if (arrel != NULL)
        delete arrel;
    //if (last_sub1 != NULL) delete last_sub1;    //TODO ja es borra amb arrel
    //if (last_sub2 != NULL) delete last_sub2;
}

void PairingStrategy::append(char c) {
    if ( arrel->n_values == size-1 ) throw(""); //TODO missatge error
    last_sub1 = new Node(c,size);
    arrel->values[arrel->n_values++] = last_sub1;
}

void PairingStrategy::appendSubLast(char c) {
    if (isEmpty()) //TODO missatge error
        throw(" ");
    last_sub1 = appendSub(last_sub1,c);
}

void PairingStrategy::appendSub2Last(char c){
    if (isEmpty()) //TODO missatge error
        throw(" ");
    int mida_aux = last_sub1->n_values;
    last_sub2 = appendSub(last_sub1->values[mida_aux],c);
}

PairingStrategy::Node::Node(char c,int size) {
    values = new Node *[size];
    n_values = 0;
    cont = c;
}

PairingStrategy::Node::~Node() {
    for ( int i = 0 ; i < n_values ; i++ ){
        delete values[i];
    }
}

bool PairingStrategy::isEmpty() const {
    return arrel->n_values == 0;
}


bool PairingStrategy::isEmpty(PairingStrategy::Node *n) const {
    return n->n_values == 0;
}

PairingStrategy::Node *PairingStrategy::appendSub(PairingStrategy::Node *n, char c) {

    Node * ret = new Node(c,size);
    if ( n->n_values == 0 ) {
        n->values[0] = new Node(n->cont,size);
        n->values[1] = ret;
        n->n_values = 2;
    }
    else {
        if (n->n_values == size-1) throw("");   //TODO missatge error
        n->values[n->n_values++] = ret;
    }

    return ret;
}





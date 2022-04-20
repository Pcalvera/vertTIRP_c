//
// Created by pauca on 10/04/2022.
//

#include "PairingStrategy.h"


PairingStrategy::PairingStrategy() {
    this->ps = list<list<Node>>();
}

void PairingStrategy::append(char c) {
    if ( this->ps.empty() ) throw("La llista és buida"); //TODO missatge error
    this->ps.back().push_back(Node(c,0));
}

void PairingStrategy::append2(char c) {
    if ( this->ps.empty() ) throw("La llista és buida"); //TODO missatge error
    list<Node> back = this->ps.back();
    if ( back.empty() ) throw("La llsita és buida");
    Node back2 = back.back();
    if ( back2.dif == 0 ) throw("");  //TODO missatge error
    this->ps.back().back().l.push_back(c);
}

void PairingStrategy::add(char c) {
    this->ps.push_back(list<Node>(1,Node(c,0)));
}

void PairingStrategy::add2(char c) {
    this->ps.push_back(list<Node>(1,Node(c,1)));
}

//void PairingStrategy::appendSubLast(char c) {
//    if (isEmpty()) //TODO missatge error
//        throw(" ");
//    last_sub1 = appendSub(last_sub1,c);
//}
//
//void PairingStrategy::appendSub2Last(char c){
//    if (isEmpty()) //TODO missatge error
//        throw(" ");
//    int mida_aux = last_sub1->n_values;
//    last_sub2 = appendSub(last_sub1->values[mida_aux],c);
//}
//
PairingStrategy::Node::Node(char c,int i) {
    dif = i;
    if ( dif == 0 )
        cont = c;
    else
        l.push_back(c);
}
//
//
//bool PairingStrategy::isEmpty() const {
//    return arrel->n_values == 0;
//}
//
//bool PairingStrategy::isEmpty(PairingStrategy::Node *n) const {
//    return n->n_values == 0;
//}
//
//PairingStrategy::Node *PairingStrategy::appendSub(PairingStrategy::Node *n, char c) {
//
//    Node * ret = new Node(c,size);
//    if ( n->n_values == 0 ) {
//        n->values[0] = new Node(n->cont,size);
//        n->values[1] = ret;
//        n->n_values = 2;
//    }
//    else {
//        if (n->n_values == size-1) throw("");   //TODO missatge error
//        n->values[n->n_values++] = ret;
//    }
//
//    return ret;
//}





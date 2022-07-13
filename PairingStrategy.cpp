//
// Created by pauca on 10/04/2022.
//

#include "PairingStrategy.h"


PairingStrategy::PairingStrategy() {
    this->ps = vector<vector<Node>>();
}

void PairingStrategy::append(char c) {
    if ( this->ps.empty() ) throw("La llista és buida"); //TODO missatge error
    this->ps.back().push_back(Node(c,0));
}

void PairingStrategy::append2(char c) {
    if ( this->ps.empty() ) throw("La llista és buida"); //TODO missatge error
    vector<Node> back = this->ps.back();
    if ( back.empty() ) throw("La llsita és buida");
    Node back2 = back.back();
    if ( back2.dif == 0 ) throw("");  //TODO missatge error
    this->ps.back().back().l.push_back(c);
}

void PairingStrategy::appendAdd(char c) {
    if ( this->ps.empty() ) throw("La llista és buida"); //TODO missatge error
        this->ps.back().push_back( Node(c,1) );
}

void PairingStrategy::add(char c) {
    this->ps.emplace_back(vector<Node>(1,Node(c,0)));
}

void PairingStrategy::add2(char c) {
    this->ps.emplace_back(vector<Node>(1,Node(c,1)));
}

bool PairingStrategy::empty() const {
    return ps.empty();
}

vector<Node> &PairingStrategy::operator[](int i) { //TODO
    return ps[i];
}

vector<vector<Node>> &PairingStrategy::get_ps() {
    return ps;
}

Node::Node(char c,int i) {
    dif = i;
    if ( dif == 0 )
        cont = c;
    else
        l.push_back(c);
}





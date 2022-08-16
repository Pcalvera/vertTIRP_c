//

#include "PairingStrategy.h"


PairingStrategy::PairingStrategy() {
    this->ps = vector<vector<Node>>();
}

//
// Created by pauca on 10/04/2022.
PairingStrategy::PairingStrategy(const PairingStrategy &o) {
    this->ps = o.ps;
}

void PairingStrategy::append(char c) {
    if ( this->ps.empty() ) throw("\"PairingStrategy->ps\" is empty");
    this->ps.back().push_back(Node(c,false));
}

void PairingStrategy::append2(char c) {
    if ( this->ps.empty() ) throw("\"PairingStrategy->ps\" is empty");
    vector<Node> back = this->ps.back();
    if ( back.empty() ) throw("Empty list");
    Node back2 = back.back();
    if ( !back2.dif ) throw("Empty list");
    this->ps.back().back().l.push_back(c);
}

void PairingStrategy::appendAdd(char c) {
    if ( this->ps.empty() ) throw("\"PairingStrategy->ps\" is empty");
        this->ps.back().push_back( Node(c,true) );
}

void PairingStrategy::add(char c) {
    this->ps.emplace_back(vector<Node>(1,Node(c,false)));
}

void PairingStrategy::add2(char c) {
    this->ps.emplace_back(vector<Node>(1,Node(c,true)));
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

Node::Node(char c,bool i) {
    dif = i;
    if ( !dif )
        cont = c;
    else
        l.push_back(c);
}





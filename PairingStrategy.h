//
// Created by pauca on 10/04/2022.
//

#ifndef VERTTIRP_C_PAIRINGSTRATEGY_H
#define VERTTIRP_C_PAIRINGSTRATEGY_H
#include <iostream>
#include "vector"

using namespace std;

struct Node {
    char cont;
    vector<char> l;

    bool dif;  //FALSE-valor    TRUE-llista valors
    Node(char c, bool i);
};

class PairingStrategy {
public:
    PairingStrategy();
    PairingStrategy(const PairingStrategy &o);
    void append(char c);
    void append2(char c);
    void appendAdd(char c);
    void add(char c);
    void add2(char c);
    bool empty()const;
    vector<vector<Node>> & get_ps();

private:
    vector<vector<Node>> ps; // representació de l’arbre
};

#endif //VERTTIRP_C_PAIRINGSTRATEGY_H

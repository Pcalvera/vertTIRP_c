//
// Created by pauca on 10/04/2022.
//

#ifndef VERTTIRP_C_PAIRINGSTRATEGY_H
#define VERTTIRP_C_PAIRINGSTRATEGY_H
#include <iostream>
#include "list"

using namespace std;

class PairingStrategy {
public:
    PairingStrategy();
    void append(char c);
    void append2(char c);
    void add(char c);
    void add2(char c);
    //void appendSubLast(char c);
    //void appendSub2Last(char c);
    //bool isEmpty() const;
private:
    struct Node {
        char cont;
        list<char> l;

        int dif;  //0-valor    1-llista valors
        Node(char c,int i);
    };
    // inv: arrel és un punter a una jerarquia disjunta de nodes (o és NULL)
    list<list<Node>> ps; // representació de l’arbre

    //bool isEmpty(Node * n) const;
    //Node * appendSub(Node * n, char c);
};
//TODO no es memory efficient

#endif //VERTTIRP_C_PAIRINGSTRATEGY_H

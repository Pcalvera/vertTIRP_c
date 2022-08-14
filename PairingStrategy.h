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
    void append(char c);
    void append2(char c);
    void appendAdd(char c);
    void add(char c);
    void add2(char c);
    bool empty()const;
    vector<Node> &operator[](int i);
    vector<vector<Node>> & get_ps();
    //Node * appendSub(Node * n, char c);
    //void appendSubLast(char c);
    //void appendSub2Last(char c);
    //bool isEmpty() const;

private:
    // inv: arrel és un punter a una jerarquia disjunta de nodes (o és NULL)
    vector<vector<Node>> ps; // representació de l’arbre

    //bool isEmpty(Node * n) const;
};
//TODO arreglar la classe

#endif //VERTTIRP_C_PAIRINGSTRATEGY_H

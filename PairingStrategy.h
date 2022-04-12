//
// Created by pauca on 10/04/2022.
//

#ifndef VERTTIRP_C_PAIRINGSTRATEGY_H
#define VERTTIRP_C_PAIRINGSTRATEGY_H
#include <iostream>



class PairingStrategy {
public:
    PairingStrategy(int size = 10);
    ~PairingStrategy();
    void append(char c);
    void appendSubLast(char c);
    void appendSub2Last(char c);
    bool isEmpty() const;
private:
    struct Node {
        char cont;
        Node **values;
        int n_values;
        Node(char c,int size);
        ~Node(); // per fer el destructor
    };
    // inv: arrel és un punter a una jerarquia disjunta de nodes (o és NULL)
    Node * arrel; // representació de l’arbre
    Node * last_sub1;
    Node * last_sub2;
    int size;

    bool isEmpty(Node * n) const;
    Node * appendSub(Node * n, char c);
};


#endif //VERTTIRP_C_PAIRINGSTRATEGY_H

//
// Created by pauca on 31/05/2022.
//

#ifndef VERTTIRP_C_VERTTIRPNODE_H
#define VERTTIRP_C_VERTTIRPNODE_H
#include <iostream>
#include <vector>
#include <memory>
#include "VertTirpSidList.h"
#include "VertTirpSidList.h"

using namespace std;

class VertTirpNode {
public:
    VertTirpNode();
    VertTirpNode(string &patt, unsigned pat_len, VertTirpSidList &sidList, bool is_root=true);
    void add_child(VertTirpNode &ch);
private:


    //struct Node {
    //    //TODO de moment prescideixo de l'atribut parent
    //    shared_ptr<Node> child,brother;
    //    string patt;
    //    unsigned pat_len;
    //    VertTirpSidList sidlist;
    //};
    //shared_ptr<Node> node;
    //bool is_root;
    //TODO de moment prescideixo de l'atribut parent
    vector<VertTirpNode> child_nodes;
    string patt;
    unsigned pat_len;
    VertTirpSidList sidlist;
    bool is_root;
};


#endif //VERTTIRP_C_VERTTIRPNODE_H

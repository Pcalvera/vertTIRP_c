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
    VertTirpNode(string &patt, unsigned pat_len, VertTirpSidList sidList, bool is_root=true);
    void add_child(shared_ptr<VertTirpNode> &ch );
    void add_childs(vector<shared_ptr<VertTirpNode>> &ch );
private:
    void add_brother(shared_ptr<VertTirpNode> &ch );
    void add_brothers(vector<shared_ptr<VertTirpNode>> &ch,int i);



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
    shared_ptr<VertTirpNode> child,brother;
    string patt;
    unsigned pat_len;
    VertTirpSidList sidlist;
    bool is_root;
};


#endif //VERTTIRP_C_VERTTIRPNODE_H

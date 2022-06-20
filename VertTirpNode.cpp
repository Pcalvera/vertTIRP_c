//
// Created by pauca on 31/05/2022.
//

#include "VertTirpNode.h"

VertTirpNode::VertTirpNode() {
    this->patt = "";
    this->pat_len = 0;
    //this->sidlist = sidList;
    //this->is_root = is_root;
    //this->child_nodes = vector<unique_ptr<VertTirpNode>>();
}

VertTirpNode::VertTirpNode(string &patt, unsigned int pat_len,  VertTirpSidList &sidList, bool is_root) {
    this->patt = patt;
    this->pat_len = pat_len;
    this->sidlist = sidList;
    this->is_root = is_root;
    this->child_nodes = vector<VertTirpNode>();
}

void VertTirpNode::add_child(VertTirpNode &ch) {
    this->child_nodes.push_back(ch);
}

//
// Created by pauca on 31/05/2022.
//

#include "VertTirpNode.h"

VertTirpNode::VertTirpNode() {
    node = shared_ptr<Node>(new Node);
    this->node->patt = "";
    this->node->pat_len = 0;
    //this->node->sidlist = sidList; //TODO no pot ser null de moment ho deixo sense inicialitzar
    this->node->is_root = true;
    this->node->child_nodes = vector<shared_ptr<Node>>();
    this->node->parent = nullptr;
}

VertTirpNode::VertTirpNode(string &patt, unsigned int pat_len,  VertTirpSidList &sidList,VertTirpNode &parent, bool is_root) {
    this->node = shared_ptr<Node>(new Node);
    this->node->patt = patt;
    this->node->pat_len = pat_len;
    this->node->sidlist = sidList;
    this->node->is_root = is_root;
    this->node->child_nodes = vector<shared_ptr<Node>>();

    if ( parent.node == nullptr ) {
        this->node->parent = nullptr;
        //this->node->is_root = true;  //TODO comprovar si fa falta (el parametre ho especifica)
    }
    else {
        this->node->parent = parent.node;
        //this->node->is_root = false;
    }
    //this->patt = patt;
    //this->pat_len = pat_len;
    //this->sidlist = sidList;
    //this->is_root = is_root;
    //this->parent = parent;
    //this->child_nodes = vector<VertTirpNode>();
}

void VertTirpNode::add_child(VertTirpNode &ch) {
    this->node->child_nodes.push_back(ch.node);
}

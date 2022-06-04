//
// Created by pauca on 31/05/2022.
//

#include "VertTirpNode.h"

VertTirpNode::VertTirpNode(string &patt, unsigned int pat_len,  VertTirpSidList sidList, bool is_root) {
    this->patt = patt;
    this->pat_len = pat_len;
    this->sidlist = sidList;
    this->is_root = is_root;
    this->child,this->brother = nullptr;
}

void VertTirpNode::add_child(shared_ptr<VertTirpNode> &ch) {
    if (this->child == nullptr)
        this->child = ch;
    else
        this->child->add_brother(ch);
}

void VertTirpNode::add_childs(vector<shared_ptr<VertTirpNode>> &ch) {
    if ( ch.size() > 0 ) {
        this->child = ch[0];
        this->child->add_brothers(ch,1);
    }
}

void VertTirpNode::add_brother(shared_ptr<VertTirpNode> &ch) {
    if ( this->brother == nullptr )
        this->brother = ch;
    else
        this->brother->add_brother(ch);
}

void VertTirpNode::add_brothers(vector<shared_ptr<VertTirpNode>> &ch, int i) {
    if ( i < ch.size() ){
        this->brother = ch[i];
        this->brother->add_brothers(ch,i+1);
    }
}
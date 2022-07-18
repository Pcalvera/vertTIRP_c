//
// Created by pauca on 31/05/2022.
//

#include "VertTirpNode.h"

VertTirpNode::VertTirpNode() {
    this->node = shared_ptr<Node>(new Node);
    this->node->patt = "";
    this->node->pat_len = 0;
    //this->node->sidlist = sidList; //TODO no pot ser null de moment ho deixo sense inicialitzar
    this->node->is_root = true;
    this->node->child_nodes = vector<shared_ptr<Node>>();
}

VertTirpNode::VertTirpNode(string &patt, unsigned int pat_len,  VertTirpSidList &sidList,VertTirpNode &parent, bool is_root) {
    this->node = shared_ptr<Node>(new Node);
    this->node->patt = patt;
    this->node->pat_len = pat_len;
    this->node->sidlist = sidList;
    this->node->is_root = is_root;
    this->node->child_nodes = vector<shared_ptr<Node>>();

    //if ( parent.node == nullptr ) {
    //    this->node->parent = nullptr;
    //    //this->node->is_root = true;  //TODO comprovar si fa falta (el parametre ho especifica)
    //}
    //else {
    //    this->node->parent = parent.node;
    //    //this->node->is_root = false;
    //}
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



void VertTirpNode::print_tree_dfs(const shared_ptr<Node> &node, unsigned int min_len, string &o_file,
                                  const map<string, unsigned int> &events_per_sequence) {
    //TODO comentaris
    ofstream file;
    if ( node->pat_len >= min_len ){
        if ( o_file != ""){

        }
        else {
            cout<<node->patt<<endl;
            for ( const auto relPair : node->sidlist.get_definitive_discovered_tirp_dict() ){
                string rel = relPair.first;
                TIRPstatistics tirp_stat = relPair.second;
                cout<< rel
                    << " # ver: " << node->sidlist.get_ver_support(tirp_stat )   //TODO potser les funcions de support han de ser doubles
                    << " # hor: " << node->sidlist.get_mean_hor_support(events_per_sequence,tirp_stat)
                    << " # duration: " << tirp_stat.get_mean_of_means_duration()
                    << endl;
            }
        }
    }

    for ( const auto &n : node->child_nodes )
        print_tree_dfs(n, min_len, o_file, events_per_sequence);
}

void VertTirpNode::print_tree_bfs(const shared_ptr<Node> &node, unsigned int min_len, string &o_file,
                                  const map<string, unsigned int> &events_per_sequence) {

}

void
VertTirpNode::print_tree(unsigned int min_len, string &o_file, const map<string, unsigned int> &events_per_sequence, bool dfs) {
    print_tree_dfs(this->node, min_len, o_file, events_per_sequence);
}


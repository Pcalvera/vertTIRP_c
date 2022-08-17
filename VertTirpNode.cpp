//
// Created by pauca on 31/05/2022.
//

#include "VertTirpNode.h"

VertTirpNode::VertTirpNode() {
    this->node = make_shared<Node>();
    this->node->patt = EMPTY;
    this->node->pat_len = 0;
    this->node->is_root = true;
    this->node->child_nodes = vector<shared_ptr<Node>>();
}

VertTirpNode::VertTirpNode(string &patt, unsigned pat_len,  const VertTirpSidList &sidList,VertTirpNode &parent, bool is_root) {
    this->node = shared_ptr<Node>(new Node);
    this->node->patt = patt;
    this->node->pat_len = pat_len;
    this->node->sidlist = sidList;
    this->node->is_root = is_root;
    this->node->child_nodes = vector<shared_ptr<Node>>();
}

void VertTirpNode::add_child(VertTirpNode &ch) {
    this->node->child_nodes.push_back(ch.node);
}

void VertTirpNode::print_tree(unsigned int min_len, string &o_file,
                              const map<string, unsigned int> &events_per_sequence, bool dfs) {
    ofstream file;
    file.open(o_file);
    if ( dfs ) {
        if ( file.is_open()) print_tree_dfs(this->node, min_len, file, events_per_sequence);
        else print_tree_dfs(this->node, min_len, cout, events_per_sequence);
    }
    else {
        if ( file.is_open()) print_tree_bfs(this->node, min_len, file, events_per_sequence);
        else print_tree_bfs(this->node, min_len, cout, events_per_sequence);
    }
    if ( file.is_open() ) file.close();
}

void VertTirpNode::print_tree_dfs(const shared_ptr<Node> &node, unsigned int min_len, ostream &stream,
                                  const map<string, unsigned int> &events_per_sequence) {

    if ( node->pat_len >= min_len ){
        stream<<node->patt<<endl;
        for ( const auto &relPair : node->sidlist.get_definitive_discovered_tirp_dict() ){
            string rel = relPair.first;
            shared_ptr<TIRPstatistics> tirp_stat = relPair.second;
            stream<< rel
                  << " # ver: " << node->sidlist.get_ver_support(tirp_stat )
                  << " # hor: " << node->sidlist.get_mean_hor_support(events_per_sequence,tirp_stat)
                  << " # duration: " << tirp_stat->get_mean_of_means_duration()
                  << endl;
        }
    }

    for ( const auto &n : node->child_nodes )
        print_tree_dfs(n, min_len, stream, events_per_sequence);
}

void VertTirpNode::print_tree_bfs(const shared_ptr<Node> &root, unsigned int min_len, ostream &stream,
                                  const map<string, unsigned int> &events_per_sequence) {
    if ( !root->is_root ) return;

    auto q = queue< reference_wrapper<const shared_ptr<Node>> >();
    q.push(root);
    unsigned current_level_count = 1;
    unsigned next_level_count = 0;

    while ( !q.empty() ){
        shared_ptr<Node> node = q.front();
        q.pop();

        // print node data
        if ( node->pat_len >= min_len ){
            for ( const auto &relPair : node->sidlist.get_definitive_discovered_tirp_dict() ){
                string rel = relPair.first;
                shared_ptr<TIRPstatistics> tirp_stat = relPair.second;

                stream << node->patt
                       << utils_unifyChars(rel)
                       << " # ver: "
                       << node->sidlist.get_ver_support(tirp_stat )
                       << " # hor: " << node->sidlist.get_mean_hor_support(events_per_sequence,tirp_stat)
                       << " # duration: " << tirp_stat->get_mean_of_means_duration()
                       << endl;
            }
        }

        // queue the children
        for ( const auto &ch : node->child_nodes){
            q.push(ch);
            next_level_count++;
        }

        current_level_count++;

        if ( current_level_count == 0 ){
            current_level_count = next_level_count;
            next_level_count = 0;
        }
    }
}
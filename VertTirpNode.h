//
// Created by pauca on 31/05/2022.
//

#ifndef VERTTIRP_C_VERTTIRPNODE_H
#define VERTTIRP_C_VERTTIRPNODE_H
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <memory>
#include "Global.h"
#include "Utils.h"
#include "VertTirpSidList.h"
#include "VertTirpSidList.h"


using namespace std;



class VertTirpNode {
public:
    struct Node {
        vector<shared_ptr<Node>> child_nodes;
        string patt;
        unsigned pat_len;
        VertTirpSidList sidlist;
        bool is_root;
    };
    VertTirpNode();
    VertTirpNode(string &patt, unsigned pat_len, const VertTirpSidList &sidList, VertTirpNode &parent, bool is_root=false);
    void add_child(VertTirpNode &ch);
    void print_tree( unsigned int min_len, string &o_file,const map<string, unsigned int> &events_per_sequence,bool dfs = true);
    static void print_tree_dfs(const shared_ptr<Node> &node, unsigned min_len, ostream &stream, const map<string,unsigned> &events_per_sequence);
    static void print_tree_bfs(const shared_ptr<Node> &root, unsigned min_len, ostream &stream, const map<string,unsigned> &events_per_sequence);

private:

    shared_ptr<Node> node;
};


#endif //VERTTIRP_C_VERTTIRPNODE_H

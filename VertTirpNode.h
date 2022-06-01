//
// Created by pauca on 31/05/2022.
//

#ifndef VERTTIRP_C_VERTTIRPNODE_H
#define VERTTIRP_C_VERTTIRPNODE_H
#include <iostream>
#include <vector>
#include "VertTirpSidList.h"

using namespace std;

class VertTirpNode {
public:
    VertTirpNode();
    VertTirpNode(vector<char> &patt, unsigned pat_len,VertTirpNode &parent, VertTirpSidList sidList);
private:
};


#endif //VERTTIRP_C_VERTTIRPNODE_H

//
// Created by 张文轩 on 2022/4/6.
//

#ifndef PROJECT_21099467D_ZHANG_WENXUAN_CHAIN_H
#define PROJECT_21099467D_ZHANG_WENXUAN_CHAIN_H

#include <iostream>
#include <vector>
#include <cstring>

#include "Block.h"

using namespace std;

class Chain
{
public:
    vector<Block> blockchain;
    Chain();
    ~Chain();
    bool ifValid(Chain Blockchain);
};

#endif //PROJECT_21099467D_ZHANG_WENXUAN_CHAIN_H

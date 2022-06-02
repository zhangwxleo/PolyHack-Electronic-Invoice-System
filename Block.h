//
// Created by 张文轩 on 2022/4/6.
//

#ifndef PROJECT_21099467D_ZHANG_WENXUAN_BLOCK_H
#define PROJECT_21099467D_ZHANG_WENXUAN_BLOCK_H

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct block{
    string preHash;
    string data;
    string timeStamp;
    int Index;
    //
    string name;
};

class Block : public block
{

public:
    string Hash;
    //constructor
    Block(){}
    Block(int index, string preHash);
    string getTime();
    void input();
    string getHash();
};

#endif //PROJECT_21099467D_ZHANG_WENXUAN_BLOCK_H


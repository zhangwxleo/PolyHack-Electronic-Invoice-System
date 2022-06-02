//
// Created by 张文轩 on 2022/4/6.
//

#include <iostream>
#include <vector>
#include "Chain.h"
#include "Block.h"

using namespace std;

// Constructor: create the genesis block in this blockchain
Chain::Chain()
{
    Block first;
    first.preHash = "0";
    first.data = "0";
    first.Index = 0;
    first.timeStamp = first.getTime();
    blockchain.push_back(first);
}

Chain::~Chain() {}

// Check if the blockchain has been changed maliciously.
//      Use the hash value and index comparison.
bool Chain::ifValid(Chain Blockchain)
{
    for (int i = 0; i<Blockchain.blockchain.size()-1; i++) {
        if (Blockchain.blockchain[i].Hash != Blockchain.blockchain[i+1].preHash ||
                Blockchain.blockchain[i].Index + 1 != Blockchain.blockchain[i+1].Index)
            return false;
    }

    return true;
}







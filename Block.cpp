//
// Created by 张文轩 on 2022/4/6.
//

#include <iostream>
#include <cstring>
#include <vector>
#include "Block.h"
#include "SHA1.hpp"

using namespace std;

// Constructor: Create a new block
Block::Block(int index, string prehash)
{
    preHash = prehash;
    Index = index;
    timeStamp = getTime();
    Hash = getHash();
}

// Get the hash value of the current block.
string Block::getHash()
{
    string s;
    s = preHash + data + timeStamp + to_string(Index);
    SHA1 checksum;
    checksum.update(s);
    char hash[41];
    strcpy(hash, checksum.final().c_str());

    return hash;
}

// Get the time stamp
string Block::getTime()
{
    time_t t;
    time(&t);
    string now = to_string(t);
    return now;
}

// Get the data to store in the current block.
void Block::input()
{
    string info;
    string buyer;
    cout<<"Please input the buyer: ";
    getline(cin,buyer);
    string solder;
    cout<<"Please input the seller: ";
    getline(cin,solder);
    string transaction_amount;
    cout<<"Please enter the transaction amount: ";
    getline(cin,transaction_amount);
    info = "buyer: "+buyer+"; seller: "+solder+"; amount: "+transaction_amount;
    data = info;
    name = buyer; //
}

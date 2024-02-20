#ifndef chains_h
#define chains_h

#include <iostream>
using namespace std;

class Node1{
public:
    int val;
    Node1 *next;
    Node1();
};

class HashTable {
public:
    Node1** HT;
    HashTable();
    int hash(int key);
    void insert(int key);
    bool found(int key);
    ~HashTable();
};


#include <iomanip>
#include <random>
#include <sstream>

int generate_id();

#endif

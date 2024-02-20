#include "chains.h"

Node1::Node1(){
    val = 0;
    next = nullptr;
}

HashTable::HashTable() {
    HT = new Node1*[10];
    for (int i = 0; i < 10; i++) {
        HT[i] = nullptr;
    }
}

int HashTable::hash(int key) {
    return key % 10;
}

void HashTable::insert(int key) {

    int hashID = hash(key);
    Node1* newNode = new Node1();
    newNode->val = key;

    if (HT[hashID] == nullptr) {
        HT[hashID] = newNode;
    }
    else {
        Node1* p = HT[hashID];
        Node1* q = HT[hashID];

        while (p!=NULL && p->val < key) {
            q = p;
            p = p->next;
        }

        if (q == HT[hashID] && key < q->val) {
            newNode->next = HT[hashID];
            HT[hashID] = newNode;
        }
        else if (q == HT[hashID] && key > q->val){
            newNode->next = q->next;
            q->next = newNode;
        }
        else {
            newNode->next = q->next;
            q->next = newNode;
        }
    }
}

bool HashTable::found(int key) {

    int hashId = hash(key);
    Node1* p = HT[hashId ];

    while (p!=NULL) {
        if (p->val == key) {
            return true;
        }
        p = p->next;
    }
    return false;
}

HashTable::~HashTable() {
    for (int i = 0; i < 10; i++) {
        Node1* p = HT[i];

        while (HT[i]!= NULL) {
            HT[i] = HT[i]->next;
            delete p;
            p = HT[i];
        }
    }

    delete[] HT;
};

#include <random>
int generate_id(){
    srand(time(NULL));
    return rand()% 8999 + 1000;
}


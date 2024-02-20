#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"

class Queue
{

public:
    Node *front, *rear;
    Queue();
    void enqueue(string name, int price);
    void dequeue();
    string getName();
    int getPrice();
    bool isEmpty();

};

#endif // QUEUE_H

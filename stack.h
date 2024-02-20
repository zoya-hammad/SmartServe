#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
#include "node.h"

class Stack {
public:
    Node* t;

    Stack();
    void push(string meal_name, string date);
    bool isEmpty();
    void pop();
    string getMeal();
    string getDate();
    Node* top();
};

#endif // STACK_H

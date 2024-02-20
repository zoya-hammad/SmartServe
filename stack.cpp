#include "stack.h"
#include <string>

Stack::Stack(){
    t = nullptr;
}


void Stack::push(string meal_name, string date) {
    Node* newNode = new Node();
    newNode->meal_name = meal_name;
    newNode->date = date;

    if (t == nullptr) {
        t = newNode;
    } else {
        newNode->next = t;
        t = newNode;
    }
}

bool Stack::isEmpty() {
    return t == nullptr;
}

void Stack::pop() {
    if (!isEmpty()) {
        Node* temp = t;
        t = t->next;
        delete temp;
        temp = nullptr;
        std::cout << "Element popped.\n";
    } else {
        std::cout << "Stack underflow.\n";
    }
}

string Stack::getMeal()
{
    if (!isEmpty())
        return t->meal_name;
    return "-1";
}

string Stack::getDate()
{
    if (!isEmpty())
        return t->date;
    return "-1";
}

Node* Stack::top() {
    if (!isEmpty()) {
        Node* temp = t;
        t = t->next;
        delete temp;
        temp = nullptr;
        return t;
    } else {
        throw std::runtime_error("Stack underflow.\n");
    }
}


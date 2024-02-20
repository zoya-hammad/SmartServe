#ifndef NODE_H
#define NODE_H

#include <string>
using namespace std;

class Node
{

public:
    string meal_name, date;
    int price;
    Node* next;
    Node();
};

#endif // NODE_H

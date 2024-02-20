#include "queue.h"

Queue::Queue()
{
    front = nullptr;
    rear = nullptr;
}

void Queue::enqueue(string name, int price)
{
    Node* newNode = new Node();
    newNode->meal_name = name;
    newNode->price = price;

    if (isEmpty()){
        front = newNode;
        rear = newNode;
        return;
    }

    rear->next = newNode;
    rear = newNode;
}

void Queue::dequeue()
{
    if (isEmpty())
        return;
    else if (front==rear)
        front = rear = nullptr;
    else{
        Node* temp = front;
        front = front->next;
        delete temp;
        temp = nullptr;
    }


}

string Queue::getName()
{
    if (!isEmpty())
        return front->meal_name;
    return "-1";
}

int Queue::getPrice()
{
    if (!isEmpty())
        return front->price;
    return -1;
}

bool Queue::isEmpty()
{
    return (front==nullptr);
}

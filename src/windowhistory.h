#ifndef WINDOWHISTORY_H
#define WINDOWHISTORY_H

#include <QWidget>

class Window;

class WindowHistory {
private:
    class Node {
    public:
        Window *window;
        Node *prevNode;
        Node *nextNode;

        Node(Window *window) : window(window), prevNode(nullptr), nextNode(nullptr) {}
    };

    Node *currentNode;

public:
    WindowHistory();

    void addWindow(Window *window);
    Window *navigateBack();
};

#endif // WINDOWHISTORY_H

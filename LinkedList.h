#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stack>

class LinkedList {
private:
    struct Node {
        char data;
        Node* next;
    };
    Node* head;

    Node* createNode(char data);

public:
    LinkedList();
    ~LinkedList();

    void insertNodeEnd(char data);
    void insertStringAtPosition(const char* str, int line, int index);
    void displayList();
    void clear();
    void appendText();
    void addNewLine();
    void saveToFile();
    void readFromFile();
    void insertTextAtPosition();
    void searchSubstring();
    void Delete();
};

#endif

#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
}

LinkedList::~LinkedList() {
    clear();
}
std::stack<LinkedList> Stack;



LinkedList::Node* LinkedList::createNode(char data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

LinkedList buffer;
int stackSize = 0;

void LinkedList::insertNodeEnd(char data) {
    Node* newNode = createNode(data);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }}

void LinkedList::insertStringAtPosition(const char* str, int line, int index) {
    Node* current = head;
    Node* prev = nullptr;
    int currentLine = 0;
    int currentPosition = 0;

    while (current != nullptr) {
        if (currentLine == line && currentPosition == index) {
            for (int i = 0; str[i] != '\0'; i++) {
                Node* newNode = createNode(str[i]);
                newNode->next = current;
                if (prev == nullptr) {
                    head = newNode;
                } else {
                    prev->next = newNode;
                }
                prev = newNode;
            }
            return;
        }

        if (current->data == '\n') {
            currentLine++;
            currentPosition = 0;
        } else {
            currentPosition++;
        }

        prev = current;
        current = current->next;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        Node* newNode = createNode(str[i]);
        if (prev != nullptr) {
            prev->next = newNode;
        } else {
            head = newNode;
        }
        prev = newNode;
    }}

void LinkedList::displayList() {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data;
        current = current->next;
    }
    cout << endl;}

void LinkedList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;}

void LinkedList::appendText() {
    string inputLine;
    cout << "Enter text to append:" << endl;
    cin.ignore(); // Clear the input buffer
    getline(cin, inputLine); // Read a line of text
    for (char c : inputLine) {
        insertNodeEnd(c);
    }
    addToStack(head);
    cout << "Your word has been saved!" << endl;}

void LinkedList::addNewLine() {
    insertNodeEnd('\n');
    cout << "New line has been added!" << endl;
}


void LinkedList::saveToFile() {
    string fileName;
    cout << "Enter the file name for saving:" << endl;
    cin >> fileName;
    ofstream file(fileName);
    if (!file) {
        cout << "Failed to open the file for writing." << endl;
    } else {
        Node* current = head;
        while (current != nullptr) {
            file.put(current->data);
            current = current->next;
        }
        file.close();
        cout << "Data has been saved to the file." << endl;
    }}

void LinkedList::readFromFile() {
    string fileName;
    cout << "Enter the file name to read:" << endl;
    cin >> fileName;
    ifstream file(fileName);
    if (!file) {
        cout << "Failed to open the file for reading." << endl;
    } else {
        char ch;
        while (file.get(ch)) {
            cout.put(ch);
        }
        file.close();
        cout << endl;
    }}

void LinkedList::insertTextAtPosition() {
    int line, index;
    string inputLine;
    cout << "Choose line and index: ";
    cin >> line >> index;
    cout << "Enter text to insert: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, inputLine);
    insertStringAtPosition(inputLine.c_str(), line, index);
    cout << "Text has been inserted!" << endl;}

void LinkedList::searchSubstring() {
    string inputLine;
    cout << "Enter the substring to search for:" << endl;
    cin.ignore(); // Clear the input buffer
    getline(cin, inputLine);

    Node* current = head;
    int lineIndex = 0;
    int inputIndex = 0;
    int line = 0;
    bool found = false;

    while (current != nullptr) {
        if (current->data == '\n') {
            line++;
            lineIndex = 0;
            current = current->next;
        } else if (current->data == inputLine[0]) {
            if (inputIndex != 0) {
                lineIndex = inputIndex;
            }
            inputIndex = 0;
            while (current->data == inputLine[inputIndex]) {
                current = current->next;
                inputIndex++;
                if (inputLine[inputIndex] == '\0') {
                    cout << "Found at line " << line << " and index " << lineIndex << endl;
                    found = true;
                    lineIndex += inputIndex;
                    inputIndex = 0;
                    break;
                }
            }
        } else {
            current = current->next;
            lineIndex++;
        }
    }

    if (!found) {
        cout << "Substring not found." << endl;
    }
}




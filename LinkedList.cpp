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

void LinkedList::Delete() {
    int line, index, numSymbolsToDelete;
    cout << "Choose line, index, and number of symbols: ";
    cin >> line >> index >> numSymbolsToDelete;


    Node* current = head;
    Node* previous = nullptr;
    int currentLine = 0;
    int currentIndex = 0;
    bool found = false;

    while (current != nullptr){
        if (currentLine == line && currentIndex == index){
            for (int i = 0; i < numSymbolsToDelete && current != nullptr; ++i) {
                Node* temporary = current;
                current = current->next;
                delete temporary;
            }

            if (previous != nullptr){
                previous->next = current;}
            else{
                head = current;
            }

            found = true;
            break;
        }
        if (current->data == '\n'){
            currentLine++;
            currentIndex = 0;
        } else{
            currentIndex++;
        }

        previous = current;
        current = current->next;
    }
    if (!found){
        cout<<"No text to delete"<<endl;
    } else{
        cout<<"The text was deleted"<<endl;
    }
}

void LinkedList::Cut() {
    buffer.clear();
    int line, index, numSymbolsToCut;
    cout << "Choose line, index, and number of symbols: ";
    cin >> line >> index >> numSymbolsToCut;

    Node* current = head;
    Node* previous = nullptr;
    int currentLine = 0;
    int currentIndex = 0;
    bool cut = false;

    while (current != nullptr) {
        if (currentLine == line && currentIndex == index) {
            for (int i = 0; i < numSymbolsToCut && current != nullptr; ++i) {
                buffer.insertNodeEnd(current->data);
                Node* temporary = current;
                current = current->next;
                delete temporary;
            }

            if (previous != nullptr) {
                previous->next = current;
            } else {
                head = current;
            }

            cut = true;
            break;
        }
        if (current->data == '\n') {
            currentLine++;
            currentIndex = 0;
        } else {
            currentIndex++;
        }

        previous = current;
        current = current->next;
    }
    if (!cut) {
        cout << "No text to cut" << endl;
    } else {
        cout << "The text was cut" << endl;
    }
}

void LinkedList::Paste() {
    int line, index;
    cout << "Choose line and index: ";
    cin >> line >> index;

    Node *current = head;
    Node *previous = nullptr;
    int currentLine = 0;
    int currentIndex = 0;
    bool pasted = false;

    while (current != nullptr) {
        if (currentLine == line && currentIndex == index) {
            Node *listCutCurrent = buffer.head;
            while (listCutCurrent != nullptr) {
                Node *newNode = createNode(listCutCurrent->data);
                if (previous != nullptr) {
                    previous->next = newNode;
                } else {
                    head = newNode;
                }
                newNode->next = current;
                previous = newNode;
                listCutCurrent = listCutCurrent->next;
            }

            pasted = true;
            break;
        }

        if (current->data == '\n') {
            currentLine++;
            currentIndex = 0;
        } else {
            currentIndex++;
        }

        previous = current;
        current = current->next;
    }

    if (!pasted) {
        cout << "No location to paste" << endl;
    } else {
        cout << "Text was pasted" << endl;
    }
}

void LinkedList::Copy() {
    buffer.clear();
    int line, index, numSymbolsToCut;
    cout << "Choose line, index, and number of symbols: ";
    cin >> line >> index >> numSymbolsToCut;

    Node* current = head;
    Node* previous = nullptr;
    int currentLine = 0;
    int currentIndex = 0;
    bool cut = false;

    while (current != nullptr) {
        if (currentLine == line && currentIndex == index) {
            for (int i = 0; i < numSymbolsToCut && current != nullptr; ++i) {
                buffer.insertNodeEnd(current->data);
                current = current->next;
            }

            cut = true;
            break;
        }
        if (current->data == '\n') {
            currentLine++;
            currentIndex = 0;
        } else {
            currentIndex++;
        }

        previous = current;
        current = current->next;
    }
    if (!cut) {
        cout << "No text to copy" << endl;
    } else {
        cout << "The text was copied" << endl;
    }
}
void LinkedList::InsertWithReplacement() {
    int line, index;
    cout << "Choose line and index: ";
    cin >> line >> index;

    string newText;
    cin.ignore();
    cout << "Write text: ";
    getline(cin, newText);

    Node* current = head;
    int currentLine = 0;
    int currentIndex = 0;
    bool inserted = false;

    while (current != nullptr) {
        if (currentLine == line && currentIndex == index) {
            for (int i = 0; newText[i] != '\0'; ++i) {
                if (current->next == nullptr) {
                    current->data = newText[i];
                    Node *newNode = createNode(newText[i+1]);
                    if (currentIndex == 0) {
                        head = newNode;
                    } else {
                        current->next = newNode;
                        current = current->next;
                    }
                } else {
                    current->data = newText[i];
                    current = current->next;
                }
            }

            inserted = true;
            break;
        }

        if (current->data == '\n') {
            currentLine++;
            currentIndex = 0;
        } else {
            currentIndex++;
        }
        current = current->next;
    }

    if (!inserted) {
        cout << "No location to insert" << endl;
    } else {
        cout << "Text was inserted!" << endl;
    }
}

void LinkedList::addToStack() {
    LinkedList newList;
    Node* current = head;

    while (current != nullptr) {
        Node* newNode = createNode(current->data);

        if (newList.head == nullptr) {
            newList.head = newNode;
        } else {
            Node* temp = newList.head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }

        current = current->next;
    }

    Stack.push(newList);
    stackSize++;
}

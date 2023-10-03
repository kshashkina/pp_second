#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {
    LinkedList list;
    int commandNumber;

    while (true) {
        cout << "Choose the command:" << endl;
        cin >> commandNumber;
        switch (commandNumber) {
            case 1:
                list.appendText();
                break;
            case 2:
                list.addNewLine();
                break;
            case 3:
                list.saveToFile();
                break;
            case 4:
                list.readFromFile();
                break;
            case 5:
                list.displayList();
                break;
            case 6:
                list.insertTextAtPosition();
                break;
            case 7:
                list.searchSubstring();
                break;
            case 8:
                list.Delete();
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                list.Cut();
                break;
            default:
                return 0;
        }
    }
}

#include <iostream>

struct Node {
    std :: string info;
    Node *next;
};

class StringTable {
    Node *head;

public:
    StringTable() {
        this->head = new Node;
        std :: cout << "Creating StringTable" << std :: endl;
        this->head->info = "";
        std :: cout << "Head created" << std :: endl;
        this->head->next = nullptr;
        std :: cout << "StringTable created" << std :: endl;
    }
    ~StringTable() {
        std :: cout << "StringTable destroyed" << std :: endl;
        Node *currentNode = head;
        while(currentNode != nullptr) {
            Node *temp = currentNode;
            currentNode = currentNode->next;
            delete temp;
        }
    }

    int addString(std :: string _info) {
        std :: cout << "Adding string: " << _info << std :: endl;
        Node *newNode = new Node;
        newNode->info = _info;

        std :: cout << "Node created " << newNode->info << std :: endl;
        std :: cout << "Head: " << this->head->info << std :: endl;
        std :: cout << (this->head->next == nullptr) << std :: endl;

        if(this->head->info == "") {
            std :: cout << "Head is null" << std :: endl;
            this->head = newNode;
            return 0;
        }
        else {
            Node *currentNode = this->head;
            std :: cout << "Current Node: " << currentNode->info << std :: endl;
            int index = 0;
            while(currentNode->next != nullptr) {
                if(currentNode->info == _info) {
                    return index;
                }
                currentNode = currentNode->next;
                index++;
            }
            currentNode->next = newNode;
            index++;
            return index;
        }
    }
};
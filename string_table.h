struct Node {
    std :: string info;
    struct Node *next;
};

class StringTable {
    struct Node *head;

public:
    StringTable() = default;
    ~StringTable() = default;

    int addString(std :: string _info) {
        Node *newNode = new Node;
        newNode->info = _info;

        if(head == nullptr) {
            head = newNode;
            return 0;
        }
        else {
            Node *currentNode = head;
            int index = 0;
            while(currentNode != nullptr) {
                if(currentNode->info == _info) {
                    return index;
                }
                currentNode = currentNode->next;
                index++;
            }
            currentNode->next = newNode;
            return index;
        }
    }
};
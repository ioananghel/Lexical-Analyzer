#include <iostream>

std :: string types[] = {
    "IDENTIFICATOR",
    "CONSTANTA INTREAGA",
    "CONSTANTA REALA",
    "CUVANT CHEIE"
};

struct Token {
    int type, value;
};

struct tokenNode {
    Token *token;
    struct tokenNode *next;
};

class TokenList {
    tokenNode *head;
    tokenNode *tail;
    int size;

    public:
        TokenList() = default;
        ~TokenList() = default;

        void addToken(Token *_token) {
            tokenNode *newNode = new tokenNode;
            newNode->token = _token;

            if(head == nullptr) {
                head = newNode;
                tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }
        }
};
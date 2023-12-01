#include <iostream>

std :: string types[] = {
    "IDENTIFICATOR",
    "CONSTANTA INTREAGA",
    "CONSTANTA REALA",
    "CUVANT CHEIE",
    "STRING",
    "OPERATOR"
};

struct Token {
    int type, value;
};

struct tokenNode {
    Token *token;
    tokenNode *next;
};

class TokenList {
    tokenNode *head;
    tokenNode *tail;
    int size;

    public:
        TokenList() {
            head = new tokenNode;
            tail = new tokenNode;

            head->token = nullptr;
            head->next = nullptr;
            tail->token = nullptr;
            tail->next = nullptr;

            std :: cout << "TokenList created" << std :: endl;

            size = 0;
        }
        ~TokenList() {
            tokenNode *currentNode = head;
            while(currentNode != nullptr) {
                tokenNode *temp = currentNode;
                currentNode = currentNode->next;
                delete temp;
            }
        }

        void addToken(Token _token) {
            std :: cout << "Adding Token: " << types[_token.type] << " " << _token.value << std :: endl;
            this->size++;
            Token *tempToken = new Token;
            tempToken->type = _token.type;
            tempToken->value = _token.value;
            std :: cout << "Temp Token created: " << types[tempToken->type] << " " << tempToken->value << std :: endl;
            tokenNode *newNode = new tokenNode;
            newNode->token = tempToken;

            std :: cout << "Token created: " << types[newNode->token->type] << " " << newNode->token->value << std :: endl;

            if(head->token == nullptr) {
                std :: cout << "=========================";
                head = newNode;
                tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }

            std :: cout << "Seeing the current token list\n";
            tokenNode *currentNode = head;
            while(currentNode != nullptr) {
                std :: cout << "\t\t" << types[currentNode->token->type] << " " << currentNode->token->value << std :: endl;
                currentNode = currentNode->next;
            }

            std :: cout << "Token added: " << types[tail->token->type] << " " << tail->token->value << std :: endl;
        }
        int getNumberOfTokens() {
            return size;
        }

        tokenNode *getHead() {
            // std :: cout << "Returning head: " << types[this->head->token->type] << " " << this->head->token->value << std :: endl;
            return this->head;
        }

        void printTokens() {
            std :: cout << "Printing tokens" << std :: endl;
            tokenNode *currentNode = head;
            std::cout << "Head: " << head->token << std :: endl;
            while(currentNode != nullptr) {
                std :: cout << "Parsing the tokens\n";
                std :: cout << types[currentNode->token->type] << " " << currentNode->token->value << std :: endl;
                currentNode = currentNode->next;
            }
            std :: cout << "Done printing tokens" << std :: endl;
        }

        Token getToken(int index) {
            std::cout << "INTO THE F\n";
            tokenNode *currentNode = head;

            std::cout << "AFTER THE F\n";

            while(index-- > 0 && currentNode->token != nullptr) {
                currentNode = currentNode->next;
            }

            if (currentNode->token == nullptr || currentNode->token == nullptr) {
                // Handle the error
                std::cerr << "Error: Invalid index or uninitialized token.\n";
                return Token(); // Return a default Token or handle the error differently
            }

            std::cout << "Found\n";
            Token tempToken;
            tempToken.type = currentNode->token->type;
            tempToken.value = currentNode->token->value;

            return tempToken;
        }

};
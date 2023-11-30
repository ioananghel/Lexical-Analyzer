#include <fstream>
#include <vector>
#include "string_table.h"
#include "token.h"

class LexicalAnalyzer {
    std :: vector<std :: string> keyWords;
    std :: vector<std :: string> operators;
    StringTable *stringTable;
    ///reference to the source file
    std::string sourceFile;
    std :: string currentLine;
    TokenList *tokenList;

public:
    LexicalAnalyzer() = default;
    LexicalAnalyzer(std :: string sourceFile) {
        std :: string keyWords[] = {"if", "else", "while", "do", "break", "continue", "int", "double", "float", "return", "char", "case", "sizeof", "long", "short", "typedef", "switch", "unsigned", "void", "static", "struct", "goto", "default", "for", "enum", "union", "register", "extern", "signed", "volatile", "const", "auto", "restrict", "bool", "complex", "imaginary", "inline", "alignas", "alignof", "atomic", "noreturn", "static_assert", "thread_local"};
        std :: string operators[] = {"+", "-", "*", "/", "%", "++", "--", "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "=", "+=", "-=", "*=", "/=", "%=", "<<=", ">>=", "&=", "^=", "|=", ",", ".", "->", "(", ")", "[", "]", "{", "}", ";", ":", "?", "#", "##", "<:", ":>"};
        this->sourceFile = sourceFile;

        for(int i = 0; i < 40; i++) {
            this->keyWords.push_back(keyWords[i]);
        }
        for(int i = 0; i < 10; i++) {
            this->operators.push_back(operators[i]);
        }

        stringTable = new StringTable();
        tokenList = new TokenList();

        std :: cout << "LexicalAnalyzer created" << std :: endl;
    }
    ~LexicalAnalyzer() {
        std :: cout << "LexicalAnalyzer destroyed" << std :: endl;
        delete stringTable;
        delete tokenList;
    }

    // get the next token from the source file
    bool makeTokens(std :: string _currentLine, bool commented, int &index) {
        std :: cout << "Making tokens on " << _currentLine << std :: endl;
        int lineLen = _currentLine.length();
        currentLine = _currentLine;

        // comments and spaces
        if(commented) {
            while(index < lineLen && (currentLine[index] != '*' && currentLine[index + 1] != '/')) {
                index++;
            }
            if(index == lineLen) {
                return 1;
            }
            else {
                index += 2;
            }
        }

        if(currentLine == "") {
            return 0;
        }
        while(index < lineLen && currentLine[index] == ' ') { index++; }

        std :: cout << "Non-white characters from " << index << std :: endl;

        if(index == lineLen) {
            return 0;
        }

        if(index + 1 < lineLen && currentLine[index] == '/' && currentLine[index + 1] == '/') {
            return 0;
        }
        if(index + 1 < lineLen && (currentLine[index] == '/' && currentLine[index + 1] == '*')) {
            commented = true;
            while(index < lineLen && currentLine[index] != '*' && currentLine[index + 1] != '/') {
                index++;
            }
            if(index == lineLen) {
                return 1;
            }
            else {
                index += 2;
            }
        }

        std :: cout << "no comments" << std :: endl;
        std :: cout << "index: " << index << " Index + 1 " << index + 1 << std :: endl;
        std :: cout << "Starting off with " << currentLine.substr(index, 1) << std :: endl;
        std :: cout << "isalpha: " << isalpha(currentLine[index]) << std :: endl;
        std :: cout << "isdigit: " << isdigit(currentLine[index]) << std :: endl;

        if(isalpha(currentLine[index]) || currentLine[index] == '_') {
            std :: string temp = currentLine.substr(index,1);
            index++;
            std :: cout << "temp: " << temp << std :: endl;
            while(index <= lineLen && (isalpha(currentLine[index]) || isdigit(currentLine[index]) || currentLine[index] == '_')) {
                temp += currentLine[index++];
            }

            std :: cout << "temp: " << temp << std :: endl;

            Token tempToken;
            tempToken.type = 0;
            tempToken.value = stringTable->addString(temp);

            std :: cout << "Adding Token: " << types[tempToken.type] << " " << tempToken.value << std :: endl;

            tokenList->addToken(tempToken);
        }
        else if(isdigit(currentLine[index])) {
            std :: string temp = currentLine.substr(index,1);
            index++;
            std :: cout << "temp: " << temp << std :: endl;
            while(index <= lineLen && isdigit(currentLine[index])) {
                temp += currentLine[index++];
            }
            std :: cout << "temp: " << temp << std :: endl;
            if(currentLine[index] == '.') {
                temp += currentLine[index++];
                while(index <= lineLen && isdigit(currentLine[index])) {
                    temp += currentLine[index++];
                }
                Token tempToken;
                tempToken.type = 2;
                tempToken.value = stringTable->addString(temp);

                tokenList->addToken(tempToken);
            }
            else {
                Token tempToken;
                tempToken.type = 1;
                tempToken.value = stringTable->addString(temp);

                tokenList->addToken(tempToken);
            }
        }
        else if(currentLine[index] == '"') {
            std :: string temp = currentLine.substr(index,1);
            while(index <= lineLen && currentLine[index] != '"') {
                temp += currentLine[index++];
            }
            temp += currentLine[index++];
            Token tempToken;
            tempToken.type = 3;
            tempToken.value = stringTable->addString(temp);

            tokenList->addToken(tempToken);
        }

        return 0;
    }

    int getNumberOfTokens() {
        return tokenList->getNumberOfTokens();
    }

    void printTokens() {
        std :: cout << "Calling tokens printer" << std :: endl;
        tokenList->printTokens();
    }

    Token getToken(int index) {
        // tokenNode *currentNode = tokenList->getHead();
        // std :: cout << "Getting token at " << index << std :: endl;
        // std :: cout << "WEEEIRD " << currentNode->token->value << std :: endl;
        // while(index--) {
        //     std :: cout << "Searching for token at " << index << std :: endl;
        //     currentNode = currentNode->next;
        // }
        // std :: cout << "Found token at " << index << std :: endl;
        // return *(currentNode->token);

        std :: cout << "Getting token at " << index << std :: endl;

        Token copy;
        copy.type = (tokenList->getToken(index)).type;
        copy.value = (tokenList->getToken(index)).value;

        std :: cout << "Returning token: " << types[copy.type] << " " << copy.value << std :: endl;

        return tokenList->getToken(index);
    }
};
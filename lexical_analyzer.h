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
    char currentCharacter;
    std :: string currentLine;
    TokenList *tokenList;

public:
    LexicalAnalyzer();
    LexicalAnalyzer(std :: string sourceFile);
    ~LexicalAnalyzer();

    // get the next token from the source file
    bool makeTokens(std :: string _currentLine, bool commented, int &index) {
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
        while(index < lineLen && currentLine[index++] == ' ') {}

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

        if(isalpha(currentLine[index]) || currentLine[index] == '_') {
            std :: string temp = currentLine[index];
            while(index <= lineLen && (isalpha(currentLine[index]) || isdigit(currentLine[index]) || currentLine[index] == '_')) {
                temp += currentLine[index++];
            }

            Token *tempToken = new Token;
            tempToken->type = 0;
            tempToken->value = stringTable->addString(temp);

            tokenList->addToken(tempToken);
        }
        else if(isdigit(currentLine[index])) {
            std :: string temp = currentLine[index];
            while(index <= lineLen && isdigit(currentLine[index])) {
                temp += currentLine[index++];
            }
            if(currentLine[index] == '.') {
                temp += currentLine[index++];
                while(index <= lineLen && isdigit(currentLine[index])) {
                    temp += currentLine[index++];
                }
                Token *tempToken = new Token;
                tempToken->type = 2;
                tempToken->value = stringTable->addString(temp);

                tokenList->addToken(tempToken);
            }
            else {
                Token *tempToken = new Token;
                tempToken->type = 1;
                tempToken->value = stringTable->addString(temp);

                tokenList->addToken(tempToken);
            }
        }
        else if(currentLine[index] == '"') {
            std :: string temp = currentLine[index];
            while(index <= lineLen && currentLine[index] != '"') {
                temp += currentLine[index++];
            }
            temp += currentLine[index++];
            Token *tempToken = new Token;
            tempToken->type = 3;
            tempToken->value = stringTable->addString(temp);

            tokenList->addToken(tempToken);
        }
    }

    int getNumberOfTokens() {
        return tokenList->size;
    }

    Token getToken(int index) {
        tokenNode *currentNode = tokenList->head;
        while(index--) {
            currentNode = currentNode->next;
        }
        return *(currentNode->token);
    }
}
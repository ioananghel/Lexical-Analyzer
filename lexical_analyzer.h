#include <fstream>
#include <vector>
#include "string_table.h"
#include "token.h"

class LexicalAnalyzer {
    std :: vector<std :: string> keyWords;
    std :: vector<std :: string> operators;
    StringTable *stringTable;
    std::string sourceFile;
    std :: string currentLine;
    TokenList *tokenList;

public:
    LexicalAnalyzer() = default;
    LexicalAnalyzer(std :: string sourceFile) {
        std :: string keyWords[] = {"if", "else", "while", "do", "break", "continue", "int", "double", "float", "return", "char", "case", "sizeof", "long", "short", "typedef", "switch", "unsigned", "void", "static", "struct", "goto", "default", "for", "enum", "union", "register", "extern", "signed", "volatile", "const", "auto", "restrict", "bool", "complex", "imaginary", "inline", "alignas", "alignof", "atomic", "noreturn", "static_assert", "thread_local"};
        std :: string operators[] = {"<<=", ">>=", "++", "--", "==", "!=", ">=", "<=", "&&", "||", "<<", ">>", "+=", "-=", "*=", "/=", "%=", "&=", "^=", "|=", "->", "##", "<:", ":>", "+", "-", "*", "/", "%", ">", "<", "!", "&", "|", "^", "~", "=", ",", ".", "(", ")", "[", "]", "{", "}", ";", ":", "?", "#"};

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

    bool getToken(std :: string _currentLine, bool commented, int &index) {
        std :: cout << "Making tokens on " << _currentLine << std :: endl;
        std :: cout << "Commented status: " << commented << std :: endl;
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
        if(index + 1 < lineLen && (currentLine[index] == '/' && currentLine[index + 1] == '*')) {
            index += 2;
            std :: cout << "Found a multi-line comment" << std :: endl;
            commented = true;
            while(index < lineLen && (currentLine[index] != '*' && currentLine[index + 1] != '/')) {
                std :: cout << "Searching for the end of the comment, at index: " << index << std :: endl;
                index++;
            }
            if(index == lineLen) {
                return 1;
            }
            else {
                index += 2;
            }
        }
        while(index < lineLen && currentLine[index] == ' ') { index++; }

        std :: cout << "Non-white characters from " << index << std :: endl;

        if(index == lineLen) {
            return 0;
        }

        if(index + 1 < lineLen && currentLine[index] == '/' && currentLine[index + 1] == '/') {
            index = lineLen;
            return 0;
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
            while(index <= lineLen && (isalpha(currentLine[index]) || isdigit(currentLine[index]) || currentLine[index] == '_' || currentLine[index] == '.')) {
                temp += currentLine[index++];
            }

            std :: cout << "temp: " << temp << std :: endl;

            Token tempToken;
            tempToken.type = 0;
            tempToken.value = stringTable->addString(temp);

            bool foundKeyWord = false;
            for(auto keyWord : keyWords) {
                if(temp == keyWord) {
                    foundKeyWord = true;
                    break;
                }
            }
            if(foundKeyWord) {
                tempToken.type = 3;
            }

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
            std :: cout << "Found a string" << std :: endl;
            std :: string temp = "\"";
            index++;
            while(index <= lineLen && currentLine[index] != '"') {
                temp += currentLine[index++];
            }

            if(currentLine[index] != '"') {
                std :: cout << "String does not end with \"" << std :: endl;
                throw "String does not end with \"";
            }
            temp += "\"";
            index++;

            std :: cout << "Temp string: " << temp << std :: endl;
            Token tempToken;
            tempToken.type = 4;
            tempToken.value = stringTable->addString(temp);

            tokenList->addToken(tempToken);
        }
        else {
            bool foundOperator = false;
            for(auto op : operators) {
                if(currentLine.substr(index, op.length()) == op) {
                    foundOperator = true;
                    Token tempToken;
                    tempToken.type = 5;
                    tempToken.value = stringTable->addString(op);

                    tokenList->addToken(tempToken);
                    index += op.length();
                    break;
                }
            }
        }

        index++;

        return 0;
    }

    int getNumberOfTokens() {
        return tokenList->getNumberOfTokens();
    }

    void printTokens() {
        std :: cout << "Calling tokens printer" << std :: endl;
        tokenList->printTokens();
    }

    Token getTokenByIndex(int index) {
        std :: cout << "Getting token at " << index << std :: endl;

        Token copy;
        copy.type = (tokenList->getToken(index)).type;
        copy.value = (tokenList->getToken(index)).value;

        std :: cout << "Returning token: " << types[copy.type] << " " << copy.value << std :: endl;

        return tokenList->getToken(index);
    }
    std :: string getFromStringTable(int index) {
        return stringTable->getString(index);
    }
};
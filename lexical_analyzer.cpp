#include "lexical_analyzer.h"

LexicalAnalyzer::LexicalAnalyzer(std :: string sourceFile) {
    std :: string keyWords[] = {"if", "else", "while", "do", "break", "continue", "int", "double", "float", "return", "char", "case", "sizeof", "long", "short", "typedef", "switch", "unsigned", "void", "static", "struct", "goto", "default", "for", "enum", "union", "register", "extern", "signed", "volatile", "const", "auto", "restrict", "bool", "complex", "imaginary", "inline", "alignas", "alignof", "atomic", "noreturn", "static_assert", "thread_local"};
    std :: string operators[] = {"+", "-", "*", "/", "%", "++", "--", "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "=", "+=", "-=", "*=", "/=", "%=", "<<=", ">>=", "&=", "^=", "|=", ",", ".", "->", "(", ")", "[", "]", "{", "}", ";", ":", "?", "#", "##", "<:", ":>"};
    this->sourceFile = sourceFile;
    this->currentCharacter = "";
    this->currentLine = 0;

    for(int i = 0; i < 47; i++) {
        this->keyWords.push_back(keyWords[i]);
    }
    for(int i = 0; i < 47; i++) {
        this->operators.push_back(operators[i]);
    }
}

LexicalAnalyzer::LexicalAnalyzer() {
    this->currentCharacter = 0;
    this->currentLine = 0;
}

LexicalAnalyzer::~LexicalAnalyzer() = default;
#pragma once
#include "../lexer/lexer.h"
#include <unordered_map>
#include <iostream>

class Interpreter {
public:
    Interpreter(Lexer& lexer);

    void interpret();

private:
    // member
    Lexer& mLexer;
    Token mCurrentToken;
    std::unordered_map<std::string, int> mVariables;

    // statements
    void eat(TokenType type);
    void assignment();
    void print();

    // expression calculation
    int expr();
    int term();
    int factor();
};

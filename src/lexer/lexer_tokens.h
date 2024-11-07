#pragma once
#include <string>

// possible token values
enum TokenType {
    LET,
    IDENTIFIER,
    NUMBER,
    SEMICOLON,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVISION,
    ASSIGNMENT,
    CONSTANT,
    PRINT,
    END,
    LEFT_PAREN,
    RIGHT_PAREN,
};

// structure of token values
struct Token {
    TokenType type;
    std::string value;
};

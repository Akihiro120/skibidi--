#include "lexer.h"
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

Lexer::Lexer(const std::string& input) {
    // instantiate member variables
    this->mInput = input;
    this->mPosition = 0;
}

Token Lexer::get_next_token() {
    // skip any whitespaces, if its not a whitespace then the character is important
    skip_whitespace(); 

    // check if end of file
    if (mPosition >= mInput.length()) {
        return Token{TokenType::END, "end"};
    }

    // get the current char at position
    char current = mInput[mPosition];

    // identifiers or keywords
    if (std::isalpha(current)) {
        // get the identifier
        std::string identifier;
        
        // loop through until a non-alphabet or number is encountered
        while (mPosition < mInput.length() && (std::isalnum(mInput[mPosition]) || mInput[mPosition] == '_')) {
            identifier += mInput[mPosition++];
        }

        // is it an operation?
        if (identifier == "skibidi") {
            // begin assignment
            return Token{TokenType::LET, identifier};
        } else if (identifier == "fr") {
            // assignment
            return Token{TokenType::ASSIGNMENT, identifier};
        } else if (identifier == "nocap") {
            // constant declaration
            return Token{TokenType::CONSTANT, identifier};
        }

        // is it an inbuilt function?
        if (identifier == "yap") {
            return Token{TokenType::PRINT, identifier};
        }
        return Token{TokenType::IDENTIFIER, identifier};
    }
    
    // numbers
    if (std::isdigit(current)) {
        // get the number
        std::string number;
        
        // loop through until a non-number value is encountered
        while (mPosition < mInput.length() && std::isdigit(mInput[mPosition])) {
            number += mInput[mPosition++];
        }
        return Token{TokenType::NUMBER, number};
    }

    // operations and punctuation
    switch (current) {
        // switch for operations
        case '+':
            mPosition++;
            return Token{TokenType::PLUS, "+"};
        case '-':
            mPosition++;
            return Token{TokenType::MINUS, "-"};
        case '*':
            mPosition++;
            return Token{TokenType::MULTIPLY, "*"};
        case '/':
            mPosition++;
            return Token{TokenType::DIVISION, "/"};
        case ';':
            mPosition++;
            return Token{TokenType::SEMICOLON, ";"};
        case '(':
            mPosition++;
            return Token{TokenType::LEFT_PAREN};
        case ')':
            mPosition++;
            return Token{TokenType::RIGHT_PAREN};
        default:
            throw std::runtime_error(
                std::string("Unknown character '") + current + "'");
    }
}   

void Lexer::skip_whitespace() {
    // check if the position is still in scope, and the input is a whitespace
    if (mPosition < mInput.length() && 
        std::isspace(mInput[mPosition]) || mInput[mPosition] == ' ' || mInput[mPosition] == '\n') {
        // skip to next position
        mPosition++;
    }
}

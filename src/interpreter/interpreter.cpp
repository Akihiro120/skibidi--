#include "interpreter.h"
#include <stdexcept>


Interpreter::Interpreter(Lexer& lexer) : mLexer(lexer) {
    // get the current token
    mCurrentToken = mLexer.get_next_token();
}

void Interpreter::interpret() {
    // continue until end of file is reached
    while (mCurrentToken.type != TokenType::END) {
        // if the token is an identifier
        if (mCurrentToken.type == TokenType::LET) {
            // assign value to identifier
            assignment();
        } else if (mCurrentToken.type == TokenType::PRINT) {
            // print operation
            print();
        } else {
            // fail, statement doesnt exist
            throw std::runtime_error("Fanum Taxed You: Invalid Statement");
        }
    }
}

void Interpreter::eat(TokenType type) {
    // this function eats the token, validating if its the intended token
    if (mCurrentToken.type == type) {
        // if it was the intented token move next
        mCurrentToken = mLexer.get_next_token();
    } else {
        // invalid token
        throw std::runtime_error(std::string("What the Sigma?: Invalid Token '" + mCurrentToken.value + "'"));
    }
}

// Assignment: skibidi IDENTIFIER fr EXPRESSION
void Interpreter::assignment() {
    eat(TokenType::LET);
    std::string var_name = mCurrentToken.value;
    eat(TokenType::IDENTIFIER);
    eat(TokenType::ASSIGNMENT);
    int value = expr();
    mVariables[var_name] = value;
}

// Print: yap EXPRESSION
void Interpreter::print() {
    eat(TokenType::PRINT);
    int value = expr();
    std::cout << value << std::endl;
}

// Expresssion: TERM ((PLUS | MINUS) TERM)
int Interpreter::expr() {
    int result = term();
    // check whether the current token is either PLUS or MINUS
    while (mCurrentToken.type == TokenType::PLUS || mCurrentToken.type == TokenType::MINUS) {
        // if the operation is PLUS
        if (mCurrentToken.type == TokenType::PLUS) {
            eat(TokenType::PLUS);
            result += term();
        }
        
        // if the operation is MINUS
        if (mCurrentToken.type == TokenType::MINUS) {
            eat(TokenType::MINUS);
            result -= term();
        }
    }
    return result;
}

// Term: FACTOR ((MUL | DIV) FACTOR)
int Interpreter::term() {
    int result = factor();

    // check whelther the token is MULTIPLY or DIVISION
    while (mCurrentToken.type == TokenType::MULTIPLY || mCurrentToken.type == TokenType::DIVISION) {
        // if the operation is multiply
        if (mCurrentToken.type == TokenType::MULTIPLY) {
            eat(TokenType::MULTIPLY);
            result *= factor();
        }

        // if the operation is division
        if (mCurrentToken.type == TokenType::DIVISION) {
            eat(TokenType::DIVISION);
            int divisor = factor();
            // prevent division by zero
            if (divisor == 0) {
                throw std::runtime_error("What the Sigma: Division by Zero");
            }
            result /= divisor;
        }
    }
    return result;
}

// Factor: NUMBER | IDENTIFIER | LPAREN expr RPAREN
int Interpreter::factor() {
    // get the current token
    Token token = mCurrentToken;

    // if the token is a number
    if (token.type == TokenType::NUMBER) {
        eat(TokenType::NUMBER);
        return std::stoi(token.value);
        // if the token is an identifier
    } else if (token.type == TokenType::IDENTIFIER) {
        eat(TokenType::IDENTIFIER);
        // does the varirable exist
        if (mVariables.find(token.value) != mVariables.end()) {
            // return the variable
            return mVariables[token.value];
        } else {
            // undefined variable error
            throw std::runtime_error("Not so Skibidi: Undefined Variable '" + token.value + "'");
        }
    } else if (token.type == TokenType::LEFT_PAREN) {
        // perform operations on brackets
        eat(TokenType::LEFT_PAREN);
        int result = expr();
        eat(TokenType::RIGHT_PAREN);
        return result;
    } else {
        // unexpected token
        throw std::runtime_error("What the Sigma: Unexpected Token in Factor: '" + token.value + "'");
    }
}

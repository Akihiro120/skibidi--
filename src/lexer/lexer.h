#pragma once
#include "lexer_tokens.h"

// the file will go through the lexer to extract into token values
class Lexer {
public:
    Lexer(const std::string& input);

    Token get_next_token();

private:
    // members
    std::string mInput = "";
    int mPosition = 0;
    
    // methods
    void skip_whitespace();
};

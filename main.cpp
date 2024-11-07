#include "src/interpreter/interpreter.h"
#include "src/lexer/lexer.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

int main(int argv, char** argc) {
    
    // get the command
    const char* operation = argc[1];

    // perform operations
    if (!strcmp(operation,"run")) {
        // run
        std::cout << "Compiling" << std::endl;
        
        // get main file
        std::ifstream main_file("main.skb");
        if (main_file.is_open()) {
            std::cout << "We in the Backrooms" << std::endl;
            
            // read main file
            std::string code = "";
            std::string line = "";
            while (std::getline(main_file, line)) {
                code += line;
            }

            // begin interpreting
            Lexer lexer(code);
            Interpreter interpreter(lexer);
            interpreter.interpret();

        } else {
            // throw runtime error
            throw std::runtime_error(
                std::string("Cant find Ohio???\nEnsure a main.skb file is present in directory"));
        }

    } else if (!strcmp(operation, "help")) {
        // help
        std::cout << "Help:" << std::endl;;
        std::cout << "run: Run the Skibidi interpreter" << std::endl;

    } else {
        // fail
        std::cout << "Operation not recognised?, use 'Skibidi help' for help" << std::endl;
    }
}

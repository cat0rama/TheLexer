#include "lexer.hpp"
#include "token.hpp"

#include <iostream>

using namespace stxa;

int main(int argc, char *argv[], char *envp[])
{
    try {
        if (Lexer::getInstance("file.txt").getToken() == Token::T_EXTERN) {
            std::cout << "extern discovered!" << std::endl;
        } else {
            std::cout << "not found!" << std::endl;
        }
    } catch (const std::runtime_error& _err) {
        std::cout << _err.what();
    }
}
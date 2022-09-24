#include "error.hpp"
#include "token.hpp"
#include "lexer.hpp"
#include "parser.hpp"

#include <iostream>
#include <iomanip>
#include <type_traits>

using namespace stxa;

int main(int argc, char *argv[], char *envp[])
{
    Parser lx("file.txt");

    while (true) {
        auto it = lx.getLastTokenData();
        if (it.m_token == Token::T_EOF) {
            break;
        } else if (it.m_token == Token::T_FUNC) {
            if (lx.parseDefinition()) {
                std::cout << "parsed a function definition" << std::endl;
            } else {
                lx.getNextToken();
            }
        } else if (it.m_token == Token::T_EXTERN) {
            if (lx.parseExtern()) {
                    std::cout << "parsed a extern" << std::endl;
            } else {
                lx.getNextToken();
            }
        } else {
            lx.getNextToken();
        }
    }

    return 0;
}
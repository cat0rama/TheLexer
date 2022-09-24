#include "error.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "token.hpp"

#include <iomanip>
#include <iostream>
#include <type_traits>

using namespace stxa;

int main(int argc, char *argv[], char *envp[])
{
    Parser lx("file.txt");

    while (true)
    {
        auto it = lx.getLastTokenData();
        if (it.m_token == Token::T_EOF) {
            break;
        }

        if (it.m_token == Token::T_EXTERN) {
            auto ex = lx.parseExtern();
            std::cout << "parsed extern" << std::endl;
            std::cout << ex->getName() << std::endl;
            for (const auto &a : ex->getArgs()) {
                std::cout << a << std::endl;
            }
            break;
        }
    }

    return 0;
}
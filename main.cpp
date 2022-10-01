#include "error.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "token.hpp"
#include "logger.hpp"

#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>

using namespace stxa;

int main(int argc, char* argv[], char* envp[]) {
    Parser lx;

    if (lx.openFile("file.txt") != Code::FILE_OPEN_ERROR) {
        auto &it = lx.getLastTokenData();
        while (lx.getLastTokenData().m_token != Token::T_EOF) {
            if (it.m_token == Token::T_EXTERN) {
                if (auto ex = lx.parseExtern()) {
                    std::cout << "parsed extern ";
                    auto args = ex->getArgs();
                    std::cout << ex->getName() << " ";
                    std::copy(args.begin(), args.end(),
                              std::ostream_iterator<std::string>(std::cout, " "));
                    std::cout << std::endl;
                } else {
                    std::cout << "signature is not defined" << std::endl;
                }
            } else if (it.m_token == Token::T_FUNC) {
                if (auto func = lx.parseDefinition()) {
                    std::cout << "parsed func ";
                    std::cout << func->getName() << std::endl;
                } else {
                    std::cout << "signature is not defined" << std::endl;
                }
            }
            lx.getNextToken();
        }
    } else {
        LOG_CRITICAL("file doesnt exist");
    }

    return 0;
}

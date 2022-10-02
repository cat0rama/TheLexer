#include "error.hpp"
#include "lexer.hpp"
#include "logger.hpp"
#include "parser.hpp"
#include "token.hpp"

#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>

using namespace stxa;

int main(int argc, char* argv[], char* envp[]) {
    Parser lx;

    if (lx.openFile("file.txt") != Code::FILE_OPEN_ERROR) {
        auto& it = lx.getLastTokenData();
        while (it.m_token != Token::T_EOF) { // Main loop
            if (it.m_token == Token::T_EXTERN) {
                if (auto ex = lx.parseExtern(); ex) {
                    std::cout << "parsed extern ";
                    auto args = ex->getArgs();
                    std::cout << ex->getName() << " ";
                    std::copy(args.begin(), args.end(),
                              std::ostream_iterator<std::string>(std::cout, " "));
                    std::cout << std::endl;
                } else {
                    // break;
                }
            } else if (it.m_token == Token::T_FUNC) {
                if (auto func = lx.parseDefinition(); func) {
                    std::cout << "parsed func ";
                    std::cout << func->getName() << std::endl;
                } else {
                    // break;
                }
            } else if (it.m_token == Token::T_NUMBER) {
                if (auto numb = lx.parseNumber(); numb) {
                    std::cout << "parsed number: " << numb->getNumber() << std::endl;
                }
            } else if (it.m_token == Token::T_ERROR) {
                LOG_CRITICAL(std::get<std::string>(it.m_data.value()), it);
                // break;
            }
            lx.getNextToken();
        }
        LOG_INFO("end of analysis file");
    } else {
        LOG_CRITICAL("file doesnt exist");
    }

    return 0;
}

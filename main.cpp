#include "lexer.hpp"
#include "token.hpp"
#include "error.hpp"

#include <iostream>
#include <iomanip>

using namespace stxa;

int main(int argc, char *argv[], char *envp[])
{
    Lexer lx("file.txt");
    
    if (lx) {
        Token token;
        while ((token = lx.getNextToken()) != Token::T_NULL) {
            switch (token)
            {
            case Token::T_FUNC:
                std::cout << "func detected: " << lx.getLastTokenData().m_file_ptr_pos << std::endl;
                break;
            case Token::T_EXTERN:
                std::cout << "extern detected: " << lx.getLastTokenData().m_file_ptr_pos << std::endl;
                break;
            case Token::T_RETURN:
                std::cout << "return detected: " << lx.getLastTokenData().m_file_ptr_pos << std::endl;
                break;
            case Token::T_NUMBER:
                std::cout << "number detected: " << std::get<double>(lx.getLastTokenData().data.value()) << std::endl;
                std::cout << "number pos: " << lx.getLastTokenData().m_file_ptr_pos << std::endl;
                break;
            case Token::T_ERROR:
                std::cout << "unable to parse number with two and more points." << std::endl;
                std::cout << lx.getLastTokenData().m_file_ptr_pos << std::endl;
                std::cout << std::get<std::string>(lx.getLastTokenData().data.value_or("identifier doesnt exist")) << std::endl;
                break;
            default:
                std::cout << "operators not found." << std::endl;
                break;
            }
        }
    }

    return 0;
}
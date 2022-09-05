#include "lexer.hpp"
#include "token.hpp"

#include <iostream>
#include <iomanip>

using namespace stxa;

int main(int argc, char *argv[], char *envp[])
{
    // Replace all with logging system
    try {
        Lexer& obj = Lexer::getInstance("file.txt");
        Token t = Token::T_NULL;

        while ((t = obj.getNextToken()) != Token::T_NULL) {
            switch (t)
            {
            case Token::T_FUNC:
                std::cout << "function detected!" << std::endl;
                break;
            case Token::T_EXTERN:
                std::cout << "extern detected!" << std::endl;
                break;
            case Token::T_RETURN:
                std::cout << "return detected!" << std::endl;
                break;
            case Token::T_NUMBER:
                std::cout << "number found: " << std::setprecision(10) 
                          << obj.m_num_value << std::endl;
                break;
            case Token::T_ERROR:
                std::cout << "unable to parse number with two and more points." << std::endl;
                break;
            default:
                std::cout << "operators not found." << std::endl;
                break;
            }
        }
    }
    catch (const std::runtime_error &_err) {
        std::cout << _err.what();
    }
}
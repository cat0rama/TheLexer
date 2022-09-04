#ifndef STXA_LEXER_HPP
#define STXA_LEXER_HPP

#include "token.hpp"

#include <string>
#include <fstream>
#include <unordered_map>

namespace stxa
{
    // Map for tokens to quickly look up values
    static const std::unordered_map<std::string, Token> identifiers = 
    {
        {"func", Token::T_FUNC},
        {"extern", Token::T_EXTERN},
        {"return", Token::T_RETURN}
    };

    // Lexer for parsing tokens from file. Singleton object
    class Lexer final
    {
    private:
        Lexer(const char* t_file_name);

        ~Lexer() = default;
    public:
    // Delete copy constructor and operator assigment
        Lexer(const Lexer&) = delete;

        Lexer& operator=(const Lexer&) = delete;
    public:
        static auto getInstance(const char* t_file_name) -> Lexer&;

        auto getToken() -> Token;
    public:
    // Variables for storing values ​​from a file of different types
        std::string m_identifier;
        double m_num_value;
    private:
        std::ifstream m_fstream;
    };
}

#endif

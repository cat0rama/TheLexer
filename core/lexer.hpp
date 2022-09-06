#ifndef STXA_LEXER_HPP
#define STXA_LEXER_HPP

#include "token.hpp"
#include "error.hpp"

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
    public:
        Lexer();

        ~Lexer() noexcept = default;
        
    // Delete copy constructor and operator assigment
        Lexer(const Lexer&) = delete;

        Lexer& operator=(const Lexer&) = delete;
    public:
        auto openFile(const std::string& t_file_name) noexcept -> Code;

        auto getNextToken() -> Token;

        auto getLastTokenData() const -> const TokenData&;
    private:
    // Variables for storing values ​​from a file of different types
        std::ifstream m_fstream;
        TokenData m_token_data;
    };
}

#endif

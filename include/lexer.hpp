#ifndef STXA_LEXER_HPP
#define STXA_LEXER_HPP

#include "token.hpp"
#include "error.hpp"

#include <string>
#include <fstream>

namespace stxa
{
    // Lexer for parsing tokens from file.
    class Lexer final 
    {
    public:
        Lexer();

        Lexer(const std::string& t_file_name) noexcept;

        ~Lexer() noexcept = default;
        
    // Delete copy constructor and operator assigment
        Lexer(const Lexer&) = delete;

        Lexer& operator=(const Lexer&) = delete;
    public:
        operator bool() const noexcept;

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

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
    // Encapsulation of some ifstream methods
        operator bool() const noexcept;

        auto openFile(const std::string& t_file_name) noexcept -> Code;

    // Methods for work with tokens
        auto getNextToken() -> Token;

        auto getLastTokenData() const -> const TokenData&;
    private:
        std::ifstream m_fstream;
    // Variable for store token metadata (token, value(C++ union), file ptr posiotion)
        TokenData m_token_data;
    public:
    // Variable that stores the last character
        char m_last_char;
    };
}

#endif

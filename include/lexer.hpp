#ifndef STXA_LEXER_HPP
#define STXA_LEXER_HPP

#include "error.hpp"
#include "token.hpp"

#include <fstream>
#include <string>

namespace stxa {
// Lexer for parsing tokens from file.
class Lexer {
  public:
    Lexer();

    Lexer(const std::string& t_file_name);

    virtual ~Lexer() noexcept = default;

    // Delete copy constructor and operator assigment
    Lexer(const Lexer&) = delete;

    Lexer& operator=(const Lexer&) = delete;

  private:
    // Other methods
    auto calculatePosition(const std::string& t_identifier) -> std::streampos;

    auto isBracket(const char t_sym) const noexcept -> bool;
    // Methods for find tokens
    auto findKeyword(std::string& t_identifier) -> bool;

    auto findNumber(std::string& t_identifier) -> bool;

    auto findComment() -> bool;

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
    char m_next_char;

  public:
    // Variable that stores the last character
    char m_last_char;

  protected:
    std::string m_identifier;
};
} // namespace stxa

#endif

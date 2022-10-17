#ifndef LEXER_LEXER_HPP
#define LEXER_LEXER_HPP

#include "error.hpp"
#include "token.hpp"

#include <fstream>
#include <string>

namespace lexer {
// Lexer for parsing tokens from file.
class Lexer {
  public:
    Lexer();

    Lexer(const std::string& t_file_name);

    ~Lexer() noexcept = default;

    // Delete copy constructor and operator assigment
    Lexer(const Lexer&) = delete;

    Lexer& operator=(const Lexer&) = delete;

  private:
    // Other methods
    auto calculatePosition(const std::string& t_identifier) -> std::streampos;

    auto isSymbol(const char t_sym) const noexcept -> bool;
    // Methods for find tokens
    auto findKeyword(std::string& t_identifier) -> bool;

    auto findNumber(std::string& t_identifier) -> bool;

    auto findComment() -> bool;

  public:
    // Encapsulation of some ifstream methods
    auto openFile(const std::string& t_file_name) noexcept -> Code;

    operator bool() const noexcept;
    // Operator for easier access data
    auto operator->() const noexcept -> const TokenData*;

    // Methods for data
    auto getNextToken() -> Token;

    auto getLastTokenData() const -> const TokenData&;

    template <typename T> auto getValue() const -> const T;

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

// Get value from std::variant with type casting from double to T(integral or real) and string
// if needed
template <typename T> auto Lexer::getValue() const -> const T {
    if constexpr ((std::is_integral_v<T> ||
                   std::is_floating_point_v<T>)) { // Check if type is number
        return static_cast<T>(
            std::get<double>(m_token_data.m_data.value_or(0))); // Return type with cast
    } else {
        return std::get<std::string>(m_token_data.m_data.value_or("null")); // Else return string
    }
}

} // namespace lexer

#endif

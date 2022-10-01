#ifndef STXA_IDENTIFIER_HPP
#define STXA_IDENTIFIER_HPP

#include "token.hpp"

#include <map>
#include <unordered_map>

namespace stxa {
// Map for binary operation precedence
inline const std::map<char, int> g_binary_precedence = {{'+', 20}, {'-', 20}, {'*', 40}, {'/', 40}};

inline const std::unordered_map<char, Token> g_symbols = {
    {';', Token::T_SEMICOLON}, {'(', Token::T_OBRACKET}, {')', Token::T_CBRACKET}};

// Map for tokens to quickly look up values (English)
inline const std::unordered_map<std::string, Token> g_identifiers_en = {
    {"func", Token::T_FUNC},
    {"extern", Token::T_EXTERN},
    {"return", Token::T_RETURN},
};

// Map for tokens to quickly look up values (Lezgi)
inline const std::unordered_map<std::string, Token> g_identifiers_lez = {

};
} // namespace stxa

#endif

#ifndef LEXER_IDENTIFIER_HPP
#define LEXER_IDENTIFIER_HPP

#include "token.hpp"

#include <map>
#include <unordered_map>

namespace lexer {
inline const std::unordered_map<char, Token> g_symbols = {{';', Token::T_SEMICOLON},
                                                          {'(', Token::T_OBRACKET},
                                                          {')', Token::T_CBRACKET},
                                                          {',', Token::T_COMMA}};

// Map for tokens to quickly look up values (English)
inline const std::unordered_map<std::string, Token> g_identifiers_en = {
    {"func", Token::T_FUNC},
    {"extern", Token::T_EXTERN},
    {"return", Token::T_RETURN},
};

} // namespace lexer

#endif

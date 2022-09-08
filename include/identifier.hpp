#ifndef STXA_IDENTIFIER_HPP
#define STXA_IDENTIFIER_HPP

#include "token.hpp"

#include <unordered_map>

namespace stxa
{
    // Map for tokens to quickly look up values
    inline const std::unordered_map<std::string, Token> identifiers_en = 
    {
        {"func", Token::T_FUNC},
        {"extern", Token::T_EXTERN},
        {"return", Token::T_RETURN}
    };
}

#endif

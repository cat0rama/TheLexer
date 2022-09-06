#ifndef STXA_TOKEN_HPP
#define STXA_TOKEN_HPP

#include <ios>
#include <variant>
#include <optional>

namespace stxa
{
    enum class Token : int
    {
        // End of file token
        T_EOF = -1,
        T_ERROR = -2,

        // Keywords
        T_FUNC = 1,
        T_EXTERN = 2,
        T_RETURN = 3,
        T_NULL = 0,

        // Identifiers
        T_IDENTIFIER = 4,
        T_NUMBER = 5
    };

    struct TokenData
    {
        // Token
        Token m_token;
        // File pointer position after identifier
        std::streamsize m_file_ptr_pos;
        // Identifier data, number or string
        std::optional<std::variant<double, std::string>> data;
    };
}

#endif

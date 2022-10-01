#ifndef STXA_TOKEN_HPP
#define STXA_TOKEN_HPP

#include <ios>
#include <optional>
#include <variant>

namespace stxa {
enum class Token : int {
    // End of file token
    T_ERROR = -2,
    T_EOF = -1,
    T_NULL = 0,
    T_OTHER = 1,

    // Keywords
    T_FUNC = 2,
    T_EXTERN = 3,
    T_RETURN = 4,
    T_COMMENT = 5,

    // Identifiers
    T_IDENTIFIER = 6,
    T_NUMBER = 7,

    // Symbols
    T_OBRACKET = 8,
    T_CBRACKET = 9,
    T_SEMICOLON = 10
};

struct TokenData {
    // Token
    Token m_token;
    // File pointer position after identifier
    std::streampos m_file_ptr_pos;
    // Identifier data, number or string
    std::optional<std::variant<double, std::string>> m_data;
    // Overload for formating log
    template <typename outStream>
    friend outStream& operator<<(outStream& t_stream, const TokenData& t_data) {
        return t_stream << "string position: [" << t_data.m_file_ptr_pos << "]";
    }
};
} // namespace stxa

#endif

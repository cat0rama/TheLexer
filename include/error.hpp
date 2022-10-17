#ifndef LEXER_ERROR_HPP
#define LEXER_ERROR_HPP

namespace lexer {
enum class Code : int {
    // Error codes
    TOKEN_ERROR = -4,
    SYMBOL_ERROR = -3,
    UNKNOWN_ERROR = -2,
    FILE_OPEN_ERROR = -1,
    SUCCES = 1
};
}

#endif

#ifndef LEXER_ERROR_HPP
#define LEXER_ERROR_HPP

namespace lexer {
enum class Code : int {
    // Error codes
    UNKNOWN_ERROR = -2,
    FILE_OPEN_ERROR = -1,

    SUCCES = 1
};
}

#endif

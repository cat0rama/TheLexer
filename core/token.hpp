#ifndef STXA_TOKEN_HPP
#define STXA_TOKEN_HPP

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
}

#endif

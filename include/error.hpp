#ifndef STXA_ERROR_HPP
#define STXA_ERROR_HPP

namespace stxa {
enum class Code : int {
    // Error codes
    UNKNOWN_ERROR = -2,
    FILE_OPEN_ERROR = -1,

    SUCCES = 1
};
}

#endif

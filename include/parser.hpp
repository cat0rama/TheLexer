#ifndef STXA_PARSE_HPP
#define STXA_PARSE_HPP

#include "exprAST.hpp"
#include "lexer.hpp"

namespace stxa
{
    // Parser for parse difference values
    class Parser : public Lexer
    {
        using expr_ptr = IExprAST::expr_ptr;
    public:
        Parser() = default;

        Parser(const std::string& t_file_name);

        ~Parser() noexcept = default;
    public:
        auto parseExpression() -> expr_ptr;

        auto parseNumber() -> expr_ptr;

        auto parseBracket() -> expr_ptr;
    };
}

#endif

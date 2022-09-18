#ifndef STXA_PARSE_HPP
#define STXA_PARSE_HPP

#include "exprAST.hpp"
#include "funcAST.hpp"
#include "lexer.hpp"

#include <type_traits>

namespace stxa
{
    // Parser for parse difference values
    class Parser : public Lexer
    {
        template<typename T>
        using expr_ptr = std::unique_ptr<T>;
    public:
        Parser() = default;

        Parser(const std::string& t_file_name);

        ~Parser() noexcept = default;
    public:
        auto parseExpression() -> expr_ptr<IExprAST>;

        auto parseNumber() -> expr_ptr<IExprAST>;

        auto parseIdentifier() -> expr_ptr<IExprAST>;

        auto parsePrototype() -> expr_ptr<IExprAST>;

        auto parseDefinition() -> expr_ptr<IExprAST>;

        auto parsePrimary() -> expr_ptr<IExprAST>;
    };
}

#endif

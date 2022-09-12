#ifndef STXA_PARSE_HPP
#define STXA_PARSE_HPP

#include "AST/exprAST.hpp"
#include "lexer.hpp"

#include <variant>

namespace stxa
{
    std::unique_ptr<IExprAST> parseExpression(Lexer& _lexer);

    std::unique_ptr<IExprAST> parseNumber(Lexer& _lexer);

    std::unique_ptr<IExprAST> parseBracket(Lexer& _lexer);
}

#endif

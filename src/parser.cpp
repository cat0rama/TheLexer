#include "parser.hpp"

#include <iostream>

namespace stxa
{
    std::unique_ptr<IExprAST> parseNumber(Lexer& _lexer)
    {
        _lexer.getNextToken();

        return std::make_unique<NumberExpr>
              (std::get<double>(_lexer.getLastTokenData().m_data.value()));
    }

    // std::unique_ptr<IExprAST> parseBracket(Lexer& _lexer)
    // {
    //     _lexer.getNextToken();
        
    //     auto v = parseExpression(_lexer);

    //     if (!v) {
    //         return nullptr;
    //     }

    //     if (_lexer.m_last_char != ')') {
    //         std::cout << "error" << std::endl;
    //     }

    //     return v;
    // }
}
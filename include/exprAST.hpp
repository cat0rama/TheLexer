#ifndef STXA_LEXER_HPP
#define STXA_LEXER_HPP


// Abstract syntax tree

namespace stxa
{
    class ExprAST
    {
    public:
        ExprAST() = default;

        virtual ~ExprAST() = default;
    };
}

#endif

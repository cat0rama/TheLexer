#include "identifier.hpp"
#include "parser.hpp"

#include <iostream>
#include <ctype.h>

namespace stxa
{
    Parser::Parser(const std::string& t_file_name): Lexer(t_file_name)
    {   }
    // prototype shit code
    auto Parser::getTokPrecedence() -> int
    {
        if (!isascii(m_last_char)) {
            return -1;
        }

        auto tok_prec = g_binary_precedence.find(m_last_char);

        if (tok_prec->second <= 0) {
            return -1;
        }

        return tok_prec->second;
    }

    auto Parser::parseNumber() -> expr_ptr<IExprAST>
    {
        auto result = std::make_unique<NumberExpr>
                     (std::get<double>(getLastTokenData().m_data.value()));

        getNextToken();

        return std::move(result);
    }

    auto Parser::parseParenExpr() -> expr_ptr<IExprAST>
    {
        getNextToken();

        auto v = parseExpression();

        if (!v) {
            return nullptr;
        }

        if (m_last_char != ')') {
            std::cout << "expected ')'" << std::endl;
            return nullptr;
        }

        getNextToken();
        return v;
    }

    auto Parser::parseIdentifier() -> expr_ptr<IExprAST>
    {
        std::string id_name = m_identifier;
        
        getNextToken();
        
        if (m_last_char != '(') {
            return std::make_unique<VariableExpr>(id_name);
        }

        getNextToken();

        std::vector<expr_ptr<IExprAST>> args;

        if (m_last_char != ')' ) {
            while (true) {
                auto arg = parseExpression();
                if (arg) {
                    args.push_back(std::move(arg));
                } else {
                    return nullptr;
                }

                if (m_last_char == ')') {
                    break;
                }

                if (m_last_char != ',') {
                    std::cout << "expected ')' or ',' in argument list" << std::endl;
                }
                getNextToken();
            }
        }

        getNextToken();
        return std::make_unique<CallExpr>(id_name, std::move(args));
    }

    auto Parser::parsePrimary() -> expr_ptr<IExprAST>
    {
        auto tok = getLastTokenData().m_token;

        if (tok == Token::T_IDENTIFIER) {
            return parseIdentifier();
        } else if (tok == Token::T_NUMBER) {
            return parseNumber();
        } else if (m_last_char == '(') {
            return parseParenExpr();
        }
    }

    
}
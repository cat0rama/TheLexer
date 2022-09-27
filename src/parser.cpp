#include "parser.hpp"
#include "identifier.hpp"

#include <ctype.h>
#include <iostream>

namespace stxa {
Parser::Parser(const std::string& t_file_name) : Lexer(t_file_name) {}
// Prototype shit code
auto Parser::getTokPrecedence() -> int {
    if (!isascii(m_last_char)) {
        return -1;
    }

    auto tok_prec = g_binary_precedence.find(m_last_char);

    if (tok_prec != g_binary_precedence.end()){
        if (tok_prec->second <= 0) {
            return -1;
        }
    } else {
        return -1;
    }

    return tok_prec->second;
}

auto Parser::parseNumber() -> expr_ptr<> {
    auto result = std::make_unique<NumberExpr>(std::get<double>(getLastTokenData().m_data.value()));

    getNextToken();

    return std::move(result);
}

auto Parser::parseParenExpr() -> expr_ptr<> {
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

auto Parser::parseIdentifier() -> expr_ptr<> {
    std::string id_name = m_identifier;

    getNextToken();

    if (m_last_char != '(') {
        return std::make_unique<VariableExpr>(id_name);
    }

    getNextToken();

    std::vector<expr_ptr<IExprAST>> args;

    if (m_last_char != ')') {
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

auto Parser::parsePrimary() -> expr_ptr<> {
    getNextToken();
    auto tok = getLastTokenData().m_token;

    if (tok == Token::T_IDENTIFIER) {
        return parseIdentifier();
    } else if (tok == Token::T_NUMBER) {
        return parseNumber();
    } else if (m_last_char == '(') {
        return parseParenExpr();
    }

    return nullptr;
}

auto Parser::parseBinaryOpRHS(int expr_prec, expr_ptr<> lhs) -> expr_ptr<> {
    while (true) {
        int tok_prec = getTokPrecedence();

        if (tok_prec < expr_prec) {
            return lhs;
        }

        int bin_op = m_last_char;

        getNextToken();

        auto rhs = parsePrimary();

        if (!rhs) {
            return nullptr;
        }

        int next_prec = getTokPrecedence();

        if (tok_prec < next_prec) {
            rhs = parseBinaryOpRHS(tok_prec + 1, std::move(rhs));
            if (!rhs) {
                return nullptr;
            }
        }

        lhs = std::make_unique<BinaryExpr>(bin_op, std::move(lhs), std::move(rhs));
    }
}

auto Parser::parseExpression() -> expr_ptr<> {
    auto lhs = parsePrimary();

    if (!lhs) {
        return nullptr;
    }

    return parseBinaryOpRHS(0, std::move(lhs));
}

auto Parser::parsePrototype() -> expr_ptr<FuncPrototype> {
    auto &data = getLastTokenData();

    if (data.m_token != Token::T_IDENTIFIER) {
        std::cout << "Expected function name in prototype" << std::endl;
        return nullptr;
    }

    std::string fn_name = m_identifier;

    getNextToken();

    if (data.m_token != Token::T_OBRACKET) {
        std::cout << "Expected '(' in prototype" << std::endl;
        return nullptr;
    }

    std::vector<std::string> arg_names;

    while (getNextToken() == Token::T_IDENTIFIER) {
        arg_names.push_back(m_identifier);
    }

    if (data.m_token != Token::T_CBRACKET) {
        std::cout << "Expceted ')' in prototype" << std::endl;
        return nullptr;
    }

    return std::make_unique<FuncPrototype>(fn_name, std::move(arg_names));
}

auto Parser::parseExtern() -> expr_ptr<FuncPrototype> {
    getNextToken();
    return parsePrototype();
}

auto Parser::parseTopLevelExpr() -> expr_ptr<FuncDefinition> {
    if (auto E = parseExpression()) {
        auto proto = std::make_unique<FuncPrototype>("", std::vector<std::string>());
        return std::make_unique<FuncDefinition>(std::move(proto), std::move(E));
    }
    return nullptr;
}

auto Parser::parseDefinition() -> expr_ptr<FuncDefinition> {
    getNextToken();

    auto proto = parsePrototype();

    if (!proto) {
        return nullptr;
    }

    if (auto E = parseExpression()) {
        return std::make_unique<FuncDefinition>(std::move(proto), std::move(E));
    }
    return nullptr;
}
} // namespace stxa

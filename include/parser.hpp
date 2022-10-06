#ifndef STXA_PARSE_HPP
#define STXA_PARSE_HPP

#include "exprAST.hpp"
#include "funcAST.hpp"
#include "lexer.hpp"

namespace stxa {
// Parser for parse difference values
class Parser : public Lexer {
    template <typename T = IExprAST> using expr_ptr = std::unique_ptr<T>;
  public:
    Parser() = default;

    Parser(const std::string& t_file_name);

    ~Parser() noexcept = default;

  public:
    // Methods for parse tokens
    auto getTokPrecedence() -> int;

    auto parseExpression() -> expr_ptr<>;

    auto parseNumber() -> expr_ptr<NumberExpr>;

    auto parseParenExpr() -> expr_ptr<>;

    auto parseIdentifier() -> expr_ptr<>;

    auto parsePrototype() -> expr_ptr<FuncPrototype>;

    auto parseDefinition() -> expr_ptr<FuncDefinition>;

    auto parsePrimary() -> expr_ptr<>;

    auto parseExtern() -> expr_ptr<FuncPrototype>;

    auto parseTopLevelExpr() -> expr_ptr<FuncDefinition>;

    auto parseBinaryOpRHS(int expr_prec, expr_ptr<> lhs) -> expr_ptr<>;
};
} // namespace stxa

#endif

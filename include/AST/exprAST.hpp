#ifndef STXA_EXPR_AST_HPP
#define STXA_EXPR_AST_HPP

#include <memory>
#include <string>
#include <vector>

// Abstract syntax tree
namespace stxa {
// Interface for expression classes
class IExprAST {
  public:
    using expr_ptr = std::unique_ptr<IExprAST>;

  public:
    IExprAST() = default;

    virtual ~IExprAST() = default;
};

// Expression class for number literals
class NumberExpr : public IExprAST {
  public:
    explicit NumberExpr(double t_value) : m_number(t_value) {}

    ~NumberExpr() = default;

  private:
    double m_number;
};

// Expression class for store variable name
class VariableExpr : public IExprAST {
  public:
    explicit VariableExpr(const std::string& t_name) : m_name(t_name) {}

    ~VariableExpr() = default;

  private:
    std::string m_name;
};

// Expression for binary operator
class BinaryExpr : public IExprAST {
  public:
    BinaryExpr(char t_op, expr_ptr t_lhs, expr_ptr t_rhs)
        : m_op(t_op), m_lhs(std::move(t_lhs)), m_rhs(std::move(t_rhs)) {}

  private:
    expr_ptr m_lhs, m_rhs;
    char m_op;
};

class CallExpr : public IExprAST {
  public:
    CallExpr(const std::string& t_name, std::vector<expr_ptr> t_args)
        : m_name(t_name), m_args(std::move(t_args)) {}

    ~CallExpr() = default;

  public:
    const std::string& getName() const { return m_name; }

  private:
    std::vector<expr_ptr> m_args;
    std::string m_name;
};
} // namespace stxa

#endif

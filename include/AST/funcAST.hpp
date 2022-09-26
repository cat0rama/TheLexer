#ifndef STXA_FUNC_AST_HPP
#define STXA_FUNC_AST_HPP

#include "exprAST.hpp"

namespace stxa {
class FuncPrototype {
  public:
    FuncPrototype(const std::string& t_name_func, std::vector<std::string> t_args)
        : m_name(t_name_func), m_args(std::move(t_args)) {}

  public:
    const std::string& getName() const { return m_name; }

    const std::vector<std::string>& getArgs() const { return m_args; }

  private:
    std::vector<std::string> m_args;
    std::string m_name;
};

class FuncDefinition {
  public:
    FuncDefinition(std::unique_ptr<FuncPrototype> t_proto, std::unique_ptr<IExprAST> t_body)
        : m_proto(std::move(t_proto)), m_body(std::move(t_body)) {}

    std::string getName() const { return m_proto->getName(); }

  private:
    std::unique_ptr<FuncPrototype> m_proto;
    std::unique_ptr<IExprAST> m_body;
};
} // namespace stxa

#endif
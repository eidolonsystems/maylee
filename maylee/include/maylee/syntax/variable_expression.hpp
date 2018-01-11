#ifndef MAYLEE_VARIABLE_EXPRESSION_HPP
#define MAYLEE_VARIABLE_EXPRESSION_HPP
#include <memory>
#include <string>
#include <utility>
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node_visitor.hpp"

namespace maylee {

  //! An expression that evaluates to a variable.
  class variable_expression : public expression {
    public:

      //! Constructs a variable expression.
      /*!
        \param l The location of the identifier token.
        \param variable The name of the variable to evaluate.
      */
      variable_expression(location l, std::string name);

      //! Returns the name of the variable to evaluate.
      const std::string& get_name() const;

      void apply(syntax_node_visitor& visitor) const override final;

    private:
      std::string m_name;
  };

  inline variable_expression::variable_expression(location l, std::string name)
      : expression(std::move(l)),
        m_name(std::move(name)) {}

  inline const std::string& variable_expression::get_name() const {
    return m_name;
  }

  inline void variable_expression::apply(syntax_node_visitor& visitor) const {
    visitor.visit(*this);
  }

  inline void syntax_node_visitor::visit(const variable_expression& node) {
    visit(static_cast<const expression&>(node));
  }
}

#endif

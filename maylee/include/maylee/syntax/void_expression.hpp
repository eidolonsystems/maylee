#ifndef MAYLEE_VOID_EXPRESSION_HPP
#define MAYLEE_VOID_EXPRESSION_HPP
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node_visitor.hpp"

namespace maylee {

  //! An expression that evaluates to a void.
  class void_expression : public expression {
    public:
      using expression::expression;

      void apply(syntax_node_visitor& visitor) const override final;
  };

  inline void void_expression::apply(syntax_node_visitor& visitor) const {
    visitor.visit(*this);
  }

  inline void syntax_node_visitor::visit(const void_expression& node) {
    visit(static_cast<const expression&>(node));
  }
}

#endif

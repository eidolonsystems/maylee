#ifndef MAYLEE_EXPRESSION_HPP
#define MAYLEE_EXPRESSION_HPP
#include "maylee/syntax/statement.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node_visitor.hpp"

namespace maylee {

  //! The base class for a syntax node representing an expression.
  class expression : public statement {
    public:
      using statement::statement;
  };

  inline void syntax_node_visitor::visit(const expression& node) {
    visit(static_cast<const statement&>(node));
  }
}

#endif

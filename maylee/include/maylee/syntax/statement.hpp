#ifndef MAYLEE_STATEMENT_HPP
#define MAYLEE_STATEMENT_HPP
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node.hpp"
#include "maylee/syntax/syntax_node_visitor.hpp"

namespace maylee {

  //! The base class for a syntax node representing a statement.
  class statement : public syntax_node {
    protected:

      //! Constructs a statement.
      statement() = default;
  };

  inline void syntax_node_visitor::visit(const statement& node) {
    visit(static_cast<const syntax_node&>(node));
  }
}

#endif

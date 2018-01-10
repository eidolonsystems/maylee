#ifndef MAYLEE_TERMINAL_NODE_HPP
#define MAYLEE_TERMINAL_NODE_HPP
#include "maylee/lexicon/terminal.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node.hpp"
#include "maylee/syntax/syntax_node_visitor.hpp"

namespace maylee {

  //! Represents a terminal token.
  class terminal_node : public syntax_node {
    public:

      //! Constructs a terminal node.
      terminal_node() = default;

      void apply(syntax_node_visitor& visitor) const override final;
  };

  inline void terminal_node::apply(syntax_node_visitor& visitor) const {
    visitor.visit(*this);
  }

  inline void syntax_node_visitor::visit(const terminal_node& node) {
    visit(static_cast<const syntax_node&>(node));
  }
}

#endif

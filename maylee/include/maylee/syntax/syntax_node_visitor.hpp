#ifndef MAYLEE_SYNTAX_NODE_VISITOR_HPP
#define MAYLEE_SYNTAX_NODE_VISITOR_HPP
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! Implements the visitor pattern for syntax nodes.
  class syntax_node_visitor {
    public:
      virtual ~syntax_node_visitor() = default;

      virtual void visit(const assignment_statement& node);

      virtual void visit(const block_statement& node);

      virtual void visit(const call_expression& node);

      virtual void visit(const expression& node);

      virtual void visit(const function_definition& node);

      virtual void visit(const if_statement& node);

      virtual void visit(const let_expression& node);

      virtual void visit(const literal_expression& node);

      virtual void visit(const return_statement& node);

      virtual void visit(const statement& node);

      virtual void visit(const syntax_node& node);

      virtual void visit(const terminal_node& node);

      virtual void visit(const type_name_expression& node);

      virtual void visit(const variable_expression& node);

      virtual void visit(const void_expression& node);

    protected:

      //! Constructs a syntax node visitor.
      syntax_node_visitor() = default;
  };

  inline void syntax_node_visitor::visit(const syntax_node& node) {}
}

#endif

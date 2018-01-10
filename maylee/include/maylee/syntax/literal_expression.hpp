#ifndef MAYLEE_LITERAL_EXPRESSION_HPP
#define MAYLEE_LITERAL_EXPRESSION_HPP
#include <utility>
#include "maylee/lexicon/literal.hpp"
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node_visitor.hpp"

namespace maylee {

  //! Represents an expression evaluating to a literal value.
  class literal_expression : public expression {
    public:

      //! Constructs a literal_expression.
      /*!
        \param literal The literal to evaluate to.
      */
      literal_expression(literal literal);

      //! Returns the literal that is evaluated.
      const literal& get_literal() const;

      void apply(syntax_node_visitor& visitor) const override final;

    private:
      literal m_literal;
  };

  inline literal_expression::literal_expression(literal literal)
      : m_literal(std::move(literal)) {}

  inline const literal& literal_expression::get_literal() const {
    return m_literal;
  }

  inline void literal_expression::apply(syntax_node_visitor& visitor) const {
    visitor.visit(*this);
  }

  inline void syntax_node_visitor::visit(const literal_expression& node) {
    visit(static_cast<const expression&>(node));
  }
}

#endif

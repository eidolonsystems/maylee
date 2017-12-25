#ifndef MAYLEE_LITERAL_EXPRESSION_HPP
#define MAYLEE_LITERAL_EXPRESSION_HPP
#include <utility>
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/lexicon/literal.hpp"

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

      const std::shared_ptr<data_type>&
        get_evaluation_type() const override final;

    private:
      literal m_literal;
  };

  inline literal_expression::literal_expression(literal literal)
      : m_literal(std::move(literal)) {}

  inline const literal& literal_expression::get_literal() const {
    return m_literal;
  }

  inline const std::shared_ptr<data_type>&
      literal_expression::get_evaluation_type() const {
    return m_literal.get_type();
  }
}

#endif

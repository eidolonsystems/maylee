#ifndef MAYLEE_IF_STATEMENT_HPP
#define MAYLEE_IF_STATEMENT_HPP
#include <memory>
#include <utility>
#include "maylee/syntax/statement.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node_visitor.hpp"
#include "maylee/syntax/void_expression.hpp"

namespace maylee {

  //! Represents an if/else statement.
  class if_statement : public statement {
    public:

      //! Constructs an if statement.
      /*!
        \param condition The condition to test.
        \param consequent The statement to execute if the condition is true.
        \param alternative The statement to execute if the condition is false.
      */
      if_statement(std::unique_ptr<expression> condition,
        std::unique_ptr<statement> consequent,
        std::unique_ptr<statement> alternative);

      //! Constructs an if statement with no alternative statement.
      /*!
        \param condition The condition to test.
        \param consequent The statement to execute if the condition is true.
      */
      if_statement(std::unique_ptr<expression> condition,
        std::unique_ptr<statement> consequent);

      //! Returns the condition that is evaluated.
      const expression& get_condition() const;

      //! Returns the statement executed if the condition is true.
      const statement& get_consequent() const;

      //! Returns the statement evaluated if the condition is false.
      const statement& get_alternative() const;

      void apply(syntax_node_visitor& visitor) const override final;

    private:
      std::unique_ptr<expression> m_condition;
      std::unique_ptr<statement> m_consequent;
      std::unique_ptr<statement> m_alternative;
  };

  inline if_statement::if_statement(std::unique_ptr<expression> condition,
      std::unique_ptr<statement> consequent,
      std::unique_ptr<statement> alternative)
      : m_condition(std::move(condition)),
        m_consequent(std::move(consequent)),
        m_alternative(std::move(alternative)) {}

  inline if_statement::if_statement(std::unique_ptr<expression> condition,
      std::unique_ptr<statement> consequent)
      : if_statement(std::move(condition), std::move(consequent),
          std::make_unique<void_expression>()) {}

  inline const expression& if_statement::get_condition() const {
    return *m_condition;
  }

  inline const statement& if_statement::get_consequent() const {
    return *m_consequent;
  }

  inline const statement& if_statement::get_alternative() const {
    return *m_alternative;
  }

  inline void if_statement::apply(syntax_node_visitor& visitor) const {
    visitor.visit(*this);
  }

  inline void syntax_node_visitor::visit(const if_statement& node) {
    visit(static_cast<const statement&>(node));
  }
}

#endif

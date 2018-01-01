#ifndef MAYLEE_IF_STATEMENT_HPP
#define MAYLEE_IF_STATEMENT_HPP
#include <memory>
#include <utility>
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node.hpp"
#include "maylee/syntax/void_expression.hpp"

namespace maylee {

  //! Represents an if/else statement.
  class if_statement : public syntax_node {
    public:

      //! Constructs an if statement.
      /*!
        \param condition The condition to test.
        \param consequent The statement to execute if the condition is true.
        \param alternative The statement to execute if the condition is false.
      */
      if_statement(std::unique_ptr<expression> condition,
        std::unique_ptr<syntax_node> consequent,
        std::unique_ptr<syntax_node> alternative);

      //! Constructs an if statement with no alternative statement.
      /*!
        \param condition The condition to test.
        \param consequent The statement to execute if the condition is true.
      */
      if_statement(std::unique_ptr<expression> condition,
        std::unique_ptr<syntax_node> consequent);

      //! Returns the condition that is evaluated.
      const expression& get_condition() const;

      //! Returns the statement executed if the condition is true.
      const syntax_node& get_consequent() const;

      //! Returns the statement evaluated if the condition is false.
      const syntax_node& get_alternative() const;

    private:
      std::unique_ptr<expression> m_condition;
      std::unique_ptr<syntax_node> m_consequent;
      std::unique_ptr<syntax_node> m_alternative;
  };

  inline if_statement::if_statement(std::unique_ptr<expression> condition,
      std::unique_ptr<syntax_node> consequent,
      std::unique_ptr<syntax_node> alternative)
      : m_condition(std::move(condition)),
        m_consequent(std::move(consequent)),
        m_alternative(std::move(alternative)) {}

  inline if_statement::if_statement(std::unique_ptr<expression> condition,
      std::unique_ptr<syntax_node> consequent)
      : if_statement(std::move(condition), std::move(consequent),
          std::make_unique<void_expression>()) {}

  inline const expression& if_statement::get_condition() const {
    return *m_condition;
  }

  inline const syntax_node& if_statement::get_consequent() const {
    return *m_consequent;
  }

  inline const syntax_node& if_statement::get_alternative() const {
    return *m_alternative;
  }
}

#endif

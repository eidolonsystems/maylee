#ifndef MAYLEE_ASSIGNMENT_STATEMENT_HPP
#define MAYLEE_ASSIGNMENT_STATEMENT_HPP
#include <memory>
#include <utility>
#include "maylee/syntax/statement.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node_visitor.hpp"

namespace maylee {

  //! Assigns an expression to an l-value.
  class assignment_statement : public statement {
    public:

      //! Constructs an assignment_statement.
      /*!
        \param destination The left hand side being assigned.
        \param value The expression to assign.
      */
      assignment_statement(std::unique_ptr<expression> destination,
        std::unique_ptr<expression> value);

      //! Returns the destination.
      const expression& get_destination() const;

      //! Returns the value to assign.
      const expression& get_value() const;

      void apply(syntax_node_visitor& visitor) const override final;

    private:
      std::unique_ptr<expression> m_destination;
      std::unique_ptr<expression> m_value;
  };

  inline assignment_statement::assignment_statement(
      std::unique_ptr<expression> destination,
      std::unique_ptr<expression> value)
      : m_destination(std::move(destination)),
        m_value(std::move(value)) {}

  inline const expression& assignment_statement::get_destination() const {
    return *m_destination;
  }

  inline const expression& assignment_statement::get_value() const {
    return *m_value;
  }

  inline void assignment_statement::apply(syntax_node_visitor& visitor) const {
    visitor.visit(*this);
  }

  inline void syntax_node_visitor::visit(const assignment_statement& node) {
    visit(static_cast<const statement&>(node));
  }
}

#endif

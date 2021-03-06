#ifndef MAYLEE_RETURN_STATEMENT_HPP
#define MAYLEE_RETURN_STATEMENT_HPP
#include <memory>
#include <utility>
#include "maylee/syntax/statement.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node_visitor.hpp"
#include "maylee/syntax/void_expression.hpp"

namespace maylee {

  //! Represents a return statement.
  class return_statement : public statement {
    public:

      //! Constructs a return statement for a Void function.
      /*!
        \param l The location of the RETURN keyword.
      */
      return_statement(location l);

      //! Constructs a return statement.
      /*!
        \param l The location of the RETURN keyword.
        \param result The expression used to produce the return value.
      */
      return_statement(location l, std::unique_ptr<expression> result);

      //! Returns the result expression.
      const expression& get_result() const;

      void apply(syntax_node_visitor& visitor) const override final;

    private:
      std::unique_ptr<expression> m_result;
  };

  inline return_statement::return_statement(location l)
      : return_statement(std::move(l),
          std::make_unique<void_expression>(location::global())) {}

  inline return_statement::return_statement(location l,
      std::unique_ptr<expression> result)
      : statement(std::move(l)),
        m_result(std::move(result)) {}

  inline const expression& return_statement::get_result() const {
    return *m_result;
  }

  inline void return_statement::apply(syntax_node_visitor& visitor) const {
    visitor.visit(*this);
  }

  inline void syntax_node_visitor::visit(const return_statement& node) {
    visit(static_cast<const statement&>(node));
  }
}

#endif

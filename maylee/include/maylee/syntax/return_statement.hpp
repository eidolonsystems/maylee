#ifndef MAYLEE_RETURN_STATEMENT_HPP
#define MAYLEE_RETURN_STATEMENT_HPP
#include <memory>
#include <utility>
#include "maylee/syntax/statement.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/void_expression.hpp"

namespace maylee {

  //! Represents a return statement.
  class return_statement : public statement {
    public:

      //! Constructs a return statement for a Void function.
      return_statement();

      //! Constructs a return statement.
      /*!
        \param result The expression used to produce the return value.
      */
      return_statement(std::unique_ptr<expression> result);

      //! Returns the result expression.
      const expression& get_result() const;

    private:
      std::unique_ptr<expression> m_result;
  };

  inline return_statement::return_statement()
      : return_statement(std::make_unique<void_expression>()) {}

  inline return_statement::return_statement(std::unique_ptr<expression> result)
      : m_result(std::move(result)) {}

  inline const expression& return_statement::get_result() const {
    return *m_result;
  }
}

#endif

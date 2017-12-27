#ifndef MAYLEE_CALL_EXPRESSION_HPP
#define MAYLEE_CALL_EXPRESSION_HPP
#include <memory>
#include <utility>
#include <vector>
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! Represents applying a callable expression to its parameters,
  //! ie. a function call.
  class call_expression : public expression {
    public:

      //! Constructs a call_expression.
      /*!
        \param callable The expression to call.
        \param parameters The parameters to apply to the <i>callable</i>.
        \param return_type The type returned by the expression.
      */
      call_expression(std::unique_ptr<expression> callable,
        std::vector<std::unique_ptr<expression>> parameters,
        std::shared_ptr<data_type> return_type);

      //! Returns the callable expression.
      const expression& get_callable() const;

      //! Returns the parameters to apply to the callable.
      const std::vector<std::unique_ptr<expression>>& get_parameters() const;

      const std::shared_ptr<data_type>&
        get_evaluation_type() const override final;

    private:
      std::unique_ptr<expression> m_callable;
      std::vector<std::unique_ptr<expression>> m_parameters;
      std::shared_ptr<data_type> m_return_type;
  };

  inline call_expression::call_expression(std::unique_ptr<expression> callable,
      std::vector<std::unique_ptr<expression>> parameters,
      std::shared_ptr<data_type> return_type)
      : m_callable(std::move(callable)),
        m_parameters(std::move(parameters)),
        m_return_type(std::move(return_type)) {}

  inline const expression& call_expression::get_callable() const {
    return *m_callable;
  }

  const std::vector<std::unique_ptr<expression>>&
      call_expression::get_parameters() const {
    return m_parameters;
  }

  inline const std::shared_ptr<data_type>&
      call_expression::get_evaluation_type() const {
    return m_return_type;
  }
}

#endif

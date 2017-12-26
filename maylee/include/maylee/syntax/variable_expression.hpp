#ifndef MAYLEE_VARIABLE_EXPRESSION_HPP
#define MAYLEE_VARIABLE_EXPRESSION_HPP
#include <memory>
#include <utility>
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/variable.hpp"

namespace maylee {

  //! An expression that evaluates to a variable.
  class variable_expression : public expression {
    public:

      //! Constructs a variable expression.
      /*!
        \param variable The variable to evaluate to.
      */
      variable_expression(std::shared_ptr<variable> variable);

      //! Returns the variable this expression evaluates to.
      const std::shared_ptr<variable>& get_variable() const;

      const std::shared_ptr<data_type>&
        get_evaluation_type() const override final;

    private:
      std::shared_ptr<variable> m_variable;
  };

  inline variable_expression::variable_expression(
      std::shared_ptr<variable> variable)
      : m_variable(std::move(variable)) {}

  inline const std::shared_ptr<variable>&
      variable_expression::get_variable() const {
    return m_variable;
  }

  inline const std::shared_ptr<data_type>&
      variable_expression::get_evaluation_type() const {
    return m_variable->get_data_type();
  }
}

#endif

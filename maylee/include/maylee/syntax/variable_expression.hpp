#ifndef MAYLEE_VARIABLE_EXPRESSION_HPP
#define MAYLEE_VARIABLE_EXPRESSION_HPP
#include <memory>
#include <string>
#include <utility>
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! An expression that evaluates to a variable.
  class variable_expression : public expression {
    public:

      //! Constructs a variable expression.
      /*!
        \param variable The name of the variable to evaluate.
      */
      variable_expression(std::string name);

      //! Returns the name of the variable to evaluate.
      const std::string& get_name() const;

    private:
      std::string m_name;
  };

  inline variable_expression::variable_expression(std::string name)
      : m_name(std::move(name)) {}

  inline const std::string& variable_expression::get_name() const {
    return m_name;
  }
}

#endif

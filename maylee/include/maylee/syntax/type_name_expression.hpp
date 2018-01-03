#ifndef MAYLEE_TYPE_NAME_EXPRESSION_HPP
#define MAYLEE_TYPE_NAME_EXPRESSION_HPP
#include <string>
#include <utility>
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! An expression that evaluates to a literal type name.
  class type_name_expression : public expression {
    public:

      //! Constructs a type name expression.
      /*!
        \param name The name of the type to evaluate to.
      */
      type_name_expression(std::string name);

      //! Returns the name of the type to evaluate to.
      const std::string& get_name() const;

    private:
      std::string m_name;
  };

  inline type_name_expression::type_name_expression(std::string name)
      : m_name(std::move(name)) {}

  inline const std::string& type_name_expression::get_name() const {
    return m_name;
  }
}

#endif

#ifndef MAYLEE_TYPE_EXPRESSION_HPP
#define MAYLEE_TYPE_EXPRESSION_HPP
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! Represents an expression that evaluates to a data type.
  class type_expression : public expression {
    protected:

      //! Constructs an empty type expression.
      type_expression() =  default;
  };
}

#endif

#ifndef MAYLEE_EXPRESSION_HPP
#define MAYLEE_EXPRESSION_HPP
#include "maylee/syntax/statement.hpp"
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! The base class for a syntax node representing an expression.
  class expression : public statement {
    protected:

      //! Constructs an expression.
      expression() = default;
  };
}

#endif

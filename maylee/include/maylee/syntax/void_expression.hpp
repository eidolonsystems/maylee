#ifndef MAYLEE_VOID_EXPRESSION_HPP
#define MAYLEE_VOID_EXPRESSION_HPP
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! An expression that evaluates to a void.
  class void_expression : public expression {
    public:

      //! Constructs a void expression.
      void_expression() = default;
  };
}

#endif

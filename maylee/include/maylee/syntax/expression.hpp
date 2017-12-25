#ifndef MAYLEE_EXPRESSION_HPP
#define MAYLEE_EXPRESSION_HPP
#include <memory>
#include "maylee/data_types/data_type.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node.hpp"

namespace maylee {

  //! The base class for a syntax node representing an expression.
  class expression : public syntax_node {
    public:
      virtual ~expression() = default;

      virtual const std::shared_ptr<data_type>& get_evaluation_type() const = 0;

    protected:

      //! Constructs an expression.
      expression() = default;
  };
}

#endif

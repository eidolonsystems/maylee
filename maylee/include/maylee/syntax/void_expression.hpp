#ifndef MAYLEE_VOID_EXPRESSION_HPP
#define MAYLEE_VOID_EXPRESSION_HPP
#include "maylee/data_types/tuple_data_type.hpp"
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! An expression that evaluates to a void.
  class void_expression : public expression {
    public:

      //! Constructs a void expression.
      void_expression() = default;

      const std::shared_ptr<data_type>&
        get_evaluation_type() const override final;
  };

  inline const std::shared_ptr<data_type>&
      void_expression::get_evaluation_type() const {
    static std::shared_ptr<data_type> v = tuple_data_type::get_void();
    return v;
  }
}

#endif

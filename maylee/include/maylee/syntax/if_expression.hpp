#ifndef MAYLEE_IF_EXPRESSION_HPP
#define MAYLEE_IF_EXPRESSION_HPP
#include <memory>
#include <string>
#include <utility>
#include "maylee/data_types/union_data_type.hpp"
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/void_expression.hpp"

namespace maylee {

  //! Represents an if/else expression.
  class if_expression : public expression {
    public:

      //! Constructs an if expression.
      /*!
        \param condition The condition to test.
        \param consequent The expression to evaluate if the condition is true.
        \param alternative The expression to evaluate if the condition is false.
      */
      if_expression(std::unique_ptr<expression> condition,
        std::unique_ptr<expression> consequent,
        std::unique_ptr<expression> alternative);

      //! Constructs an if expression whose alternative is a Void expression.
      /*!
        \param condition The condition to test.
        \param consequent The expression to evaluate if the condition is true.
      */
      if_expression(std::unique_ptr<expression> condition,
        std::unique_ptr<expression> consequent);

      //! Returns the condition that is evaluated.
      const expression& get_condition() const;

      //! Returns the expression evaluated if the condition is true.
      const expression& get_consequent() const;

      //! Returns the expression evaluated if the condition is false.
      const expression& get_alternative() const;

      const std::shared_ptr<data_type>&
        get_evaluation_type() const override final;

    private:
      std::unique_ptr<expression> m_condition;
      std::unique_ptr<expression> m_consequent;
      std::unique_ptr<expression> m_alternative;
      std::shared_ptr<data_type> m_data_type;
  };

  inline if_expression::if_expression(std::unique_ptr<expression> condition,
      std::unique_ptr<expression> consequent,
      std::unique_ptr<expression> alternative)
      : m_condition(std::move(condition)),
        m_consequent(std::move(consequent)),
        m_alternative(std::move(alternative)) {
    m_data_type = make_union_data_type({m_consequent->get_evaluation_type(),
      m_alternative->get_evaluation_type()});
  }

  inline if_expression::if_expression(std::unique_ptr<expression> condition,
      std::unique_ptr<expression> consequent)
      : if_expression(std::move(condition), std::move(consequent),
          std::make_unique<void_expression>()) {}

  inline const expression& if_expression::get_condition() const {
    return *m_condition;
  }

  inline const expression& if_expression::get_consequent() const {
    return *m_consequent;
  }

  inline const expression& if_expression::get_alternative() const {
    return *m_alternative;
  }

  inline const std::shared_ptr<data_type>&
      if_expression::get_evaluation_type() const {
    return m_data_type;
  }
}

#endif

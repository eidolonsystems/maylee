#ifndef MAYLEE_CALL_EXPRESSION_HPP
#define MAYLEE_CALL_EXPRESSION_HPP
#include <memory>
#include <utility>
#include <vector>
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node_visitor.hpp"

namespace maylee {

  //! Represents applying a callable expression to its parameters,
  //! ie. a function call.
  class call_expression : public expression {
    public:

      //! Constructs a call_expression.
      /*!
        \param callable The expression to call.
        \param parameters The parameters to apply to the <i>callable</i>.
      */
      call_expression(std::unique_ptr<expression> callable,
        std::vector<std::unique_ptr<expression>> parameters);

      //! Returns the callable expression.
      const expression& get_callable() const;

      //! Returns the parameters to apply to the callable.
      const std::vector<std::unique_ptr<expression>>& get_parameters() const;

      void apply(syntax_node_visitor& visitor) const override final;

    private:
      std::unique_ptr<expression> m_callable;
      std::vector<std::unique_ptr<expression>> m_parameters;
  };

  inline call_expression::call_expression(std::unique_ptr<expression> callable,
      std::vector<std::unique_ptr<expression>> parameters)
      : m_callable(std::move(callable)),
        m_parameters(std::move(parameters)) {}

  inline const expression& call_expression::get_callable() const {
    return *m_callable;
  }

  inline const std::vector<std::unique_ptr<expression>>&
      call_expression::get_parameters() const {
    return m_parameters;
  }

  inline void call_expression::apply(syntax_node_visitor& visitor) const {
    visitor.visit(*this);
  }

  inline void syntax_node_visitor::visit(const call_expression& node) {
    visit(static_cast<const expression&>(node));
  }
}

#endif

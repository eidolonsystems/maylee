#ifndef MAYLEE_TYPE_NAME_EXPRESSION_HPP
#define MAYLEE_TYPE_NAME_EXPRESSION_HPP
#include <string>
#include <utility>
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node_visitor.hpp"

namespace maylee {

  //! An expression that evaluates to a literal type name.
  class type_name_expression : public expression {
    public:

      //! Constructs a type name expression.
      /*! 
        \param l The location of the identifier token.
        \param name The name of the type to evaluate to.
      */
      type_name_expression(location l, std::string name);

      //! Returns the name of the type to evaluate to.
      const std::string& get_name() const;

      void apply(syntax_node_visitor& visitor) const override final;

    private:
      std::string m_name;
  };

  inline type_name_expression::type_name_expression(location l,
      std::string name)
      : expression(std::move(l)),
        m_name(std::move(name)) {}

  inline const std::string& type_name_expression::get_name() const {
    return m_name;
  }

  inline void type_name_expression::apply(syntax_node_visitor& visitor) const {
    visitor.visit(*this);
  }

  inline void syntax_node_visitor::visit(const type_name_expression& node) {
    visit(static_cast<const expression&>(node));
  }
}

#endif

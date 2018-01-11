#ifndef MAYLEE_LET_EXPRESSION_HPP
#define MAYLEE_LET_EXPRESSION_HPP
#include <memory>
#include <string>
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node_visitor.hpp"

namespace maylee {

  //! Represents a variable declaration.
  class let_expression : public expression {
    public:

      //! Constructs a let_expression.
      /*!
        \param l The location of the LET keyword.
        \param name The name of the variable.
        \param initializer The expression used to initialize the variable.
      */
      let_expression(location l, std::string name,
        std::unique_ptr<expression> initializer);

      //! Returns the name of the variable.
      const std::string& get_name() const;

      //! Returns the initializer.
      const expression& get_initializer() const;

      void apply(syntax_node_visitor& visitor) const override final;

    private:
      std::string m_name;
      std::unique_ptr<expression> m_initializer;
  };

  inline let_expression::let_expression(location l, std::string name,
      std::unique_ptr<expression> initializer)
      : expression(std::move(l)),
        m_name(std::move(name)),
        m_initializer(std::move(initializer)) {}

  inline const std::string& let_expression::get_name() const {
    return m_name;
  }

  inline const expression& let_expression::get_initializer() const {
    return *m_initializer;
  }

  inline void let_expression::apply(syntax_node_visitor& visitor) const {
    visitor.visit(*this);
  }

  inline void syntax_node_visitor::visit(const let_expression& node) {
    visit(static_cast<const expression&>(node));
  }
}

#endif

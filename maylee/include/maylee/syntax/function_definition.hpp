#ifndef MAYLEE_FUNCTION_DEFINITION_HPP
#define MAYLEE_FUNCTION_DEFINITION_HPP
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/statement.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node_visitor.hpp"

namespace maylee {

  //! Represents a function definition.
  class function_definition : public statement {
    public:

      //! Stores a function parameter.
      struct parameter {

        //! The name of the parameter.
        std::string m_name;

        //! The parameter's type.
        std::unique_ptr<expression> m_type;
      };

      //! Constructs a function definition.
      /*!
        \param name The name of the function.
        \param parameters The list of parameters.
        \param body The function's body.
      */
      function_definition(std::string name, std::vector<parameter> parameters,
        std::unique_ptr<statement> body);

      //! Returns the name of the function.
      const std::string& get_name() const;

      //! Returns the list of parameters.
      const std::vector<parameter>& get_parameters() const;

      //! Returns the function's body.
      const statement& get_body() const;

      void apply(syntax_node_visitor& visitor) const override final;

    private:
      std::string m_name;
      std::vector<parameter> m_parameters;
      std::unique_ptr<statement> m_body;
  };

  inline function_definition::function_definition(std::string name,
      std::vector<parameter> parameters, std::unique_ptr<statement> body)
      : m_name(std::move(name)),
        m_parameters(std::move(parameters)),
        m_body(std::move(body)) {}

  inline const std::string& function_definition::get_name() const {
    return m_name;
  }

  inline const std::vector<function_definition::parameter>&
      function_definition::get_parameters() const {
    return m_parameters;
  }

  inline const statement& function_definition::get_body() const {
    return *m_body;
  }

  inline void function_definition::apply(syntax_node_visitor& visitor) const {
    visitor.visit(*this);
  }

  inline void syntax_node_visitor::visit(const function_definition& node) {
    visit(static_cast<const statement&>(node));
  }
}

#endif

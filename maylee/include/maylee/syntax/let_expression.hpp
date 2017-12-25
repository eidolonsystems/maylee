#ifndef MAYLEE_LET_EXPRESSION_HPP
#define MAYLEE_LET_EXPRESSION_HPP
#include <memory>
#include <string>
#include "maylee/data_types/data_type.hpp"
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! Represents a variable declaration.
  class let_expression : public expression {
    public:

      //! Constructs a let_expression.
      /*!
        \param name The name of the variable.
        \param data_type The variable's data type.
        \param initializer The expression used to initialize the variable.
      */
      let_expression(std::string name, std::shared_ptr<data_type> data_type,
        std::unique_ptr<expression> initializer);

      //! Returns the name of the variable.
      const std::string& get_name() const;

      //! Returns the variable's data type.
      const std::shared_ptr<data_type>& get_data_type() const;

      //! Returns the initializer.
      const expression& get_initializer() const;

      const std::shared_ptr<data_type>&
        get_evaluation_type() const override final;

    private:
      std::string m_name;
      std::shared_ptr<data_type> m_data_type;
      std::unique_ptr<expression> m_initializer;
  };

  inline let_expression::let_expression(std::string name,
      std::shared_ptr<data_type> data_type,
      std::unique_ptr<expression> initializer)
      : m_name(std::move(name)),
        m_data_type(std::move(data_type)),
        m_initializer(std::move(initializer)) {}

  inline const std::string& let_expression::get_name() const {
    return m_name;
  }

  inline const std::shared_ptr<data_type>&
      let_expression::get_data_type() const {
    return m_data_type;
  }

  inline const expression& let_expression::get_initializer() const {
    return *m_initializer;
  }

  inline const std::shared_ptr<data_type>&
      let_expression::get_evaluation_type() const {
    return m_data_type;
  }
}

#endif

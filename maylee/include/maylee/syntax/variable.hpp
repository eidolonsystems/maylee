#ifndef MAYLEE_VARIABLE_HPP
#define MAYLEE_VARIABLE_HPP
#include <memory>
#include <string>
#include <utility>
#include "maylee/data_types/data_type.hpp"
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! Represents a variable.
  class variable {
    public:

      //! Constructs a variable.
      /*!
        \param name The name of the variable.
        \param data_type The variable's data type.
      */
      variable(std::string name, std::shared_ptr<data_type> data_type);

      //! Returns the name of the variable.
      const std::string& get_name() const;

      //! Returns the variable's data type.
      const std::shared_ptr<data_type>& get_data_type() const;

    private:
      std::string m_name;
      std::shared_ptr<data_type> m_data_type;
  };

  inline variable::variable(std::string name,
      std::shared_ptr<data_type> data_type)
      : m_name(std::move(name)),
        m_data_type(std::move(data_type)) {}

  inline const std::string& variable::get_name() const {
    return m_name;
  }

  inline const std::shared_ptr<data_type>& variable::get_data_type() const {
    return m_data_type;
  }
}

#endif

#ifndef MAYLEE_VARIABLE_HPP
#define MAYLEE_VARIABLE_HPP
#include "maylee/data_types/data_type.hpp"
#include "maylee/semantics/element.hpp"

namespace maylee {

  //! Represents a variable.
  class variable : public element {
    public:

      //! Constructs a variable.
      /*!
        \param l The location where the variable was declared.
        \param name The name of the variable.
        \param data_type The variable's data type.
      */
      variable(location l, std::string name,
        std::shared_ptr<data_type> data_type);

      const location& get_location() const override final;

      const std::string& get_name() const override final;

      //! Returns the variable's data type.
      const std::shared_ptr<data_type>& get_data_type() const;

    private:
      location m_location;
      std::string m_name;
      std::shared_ptr<data_type> m_data_type;
  };

  inline variable::variable(location l, std::string name,
      std::shared_ptr<data_type> data_type)
      : m_location(std::move(l)),
        m_name(std::move(name)),
        m_data_type(std::move(data_type)) {}

  inline const location& variable::get_location() const {
    return m_location;
  }

  inline const std::string& variable::get_name() const {
    return m_name;
  }

  inline const std::shared_ptr<data_type>& variable::get_data_type() const {
    return m_data_type;
  }
}

#endif

#ifndef MAYLEE_VARIABLE_HPP
#define MAYLEE_VARIABLE_HPP
#include "maylee/semantics/element.hpp"

namespace maylee {

  //! Represents a variable.
  class variable : public element {
    public:

      //! Constructs a variable.
      /*!
        \param l The location where the variable was declared.
        \param name The name of the variable.
      */
      variable(location l, std::string name);

      const location& get_location() const override final;

      const std::string& get_name() const override final;

    private:
      location m_location;
      std::string m_name;
  };

  inline variable::variable(location l, std::string name)
      : m_location(std::move(l)),
        m_name(std::move(name)) {}

  inline const location& variable::get_location() const {
    return m_location;
  }

  inline const std::string& variable::get_name() const {
    return m_name;
  }
}

#endif

#ifndef MAYLEE_VARIABLE_HPP
#define MAYLEE_VARIABLE_HPP
#include <string>
#include <utility>
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! Represents a variable.
  class variable {
    public:

      //! Constructs a variable.
      /*!
        \param name The name of the variable.
      */
      variable(std::string name);

      virtual ~variable() = default;

      //! Returns the name of the variable.
      const std::string& get_name() const;

    private:
      std::string m_name;
  };

  inline variable::variable(std::string name)
      : m_name(std::move(name)) {}

  inline const std::string& variable::get_name() const {
    return m_name;
  }
}

#endif

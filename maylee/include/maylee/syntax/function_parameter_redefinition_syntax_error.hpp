#ifndef MAYLEE_FUNCTION_PARAMETER_REDEFINITION_SYNTAX_ERROR_HPP
#define MAYLEE_FUNCTION_PARAMETER_REDEFINITION_SYNTAX_ERROR_HPP
#include <string>
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_error.hpp"

namespace maylee {

  //! Indicates a function parameter already exists with a specified name.
  class function_parameter_redefinition_syntax_error : public syntax_error {
    public:

      //! Constructs a function parameter redefinition syntax erorr.
      /*!
        \param error_location The location of the redefinition.
        \param name The name of the identifier being redefined.
        \param original_location The location of the original identifier.
      */
      function_parameter_redefinition_syntax_error(location error_location,
        std::string name, location original_location);

      //! Returns the name of the identifier being redefined.
      const std::string& get_name() const;

      //! Returns the location of the original identifier.
      const location& get_original_location() const;

    private:
      std::string m_name;
      location m_original_location;
  };

  inline function_parameter_redefinition_syntax_error::
      function_parameter_redefinition_syntax_error(location error_location,
      std::string name, location original_location)
      : syntax_error(syntax_error_code::FUNCTION_PARAMETER_ALREADY_DEFINED,
          std::move(error_location)),
        m_name(std::move(name)),
        m_original_location(std::move(original_location)) {}

  inline const std::string& function_parameter_redefinition_syntax_error::
      get_name() const {
    return m_name;
  }

  inline const location& function_parameter_redefinition_syntax_error::
      get_original_location() const {
    return m_original_location;
  }
}

#endif

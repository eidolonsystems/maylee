#ifndef MAYLEE_FUNCTION_NOT_FOUND_SYNTAX_ERROR_HPP
#define MAYLEE_FUNCTION_NOT_FOUND_SYNTAX_ERROR_HPP
#include <string>
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_error.hpp"

namespace maylee {

  //! Indicates that a function with a specified name was not found.
  class function_not_found_syntax_error : public syntax_error {
    public:

      //! Constructs a function not found syntax error.
      /*!
        \param error_location The location of the function call.
        \param name The name of the function.
      */
      function_not_found_syntax_error(location error_location,
        std::string name);

      //! Returns the name of the function.
      const std::string& get_name() const;

    private:
      std::string m_name;
  };

  inline function_not_found_syntax_error::function_not_found_syntax_error(
      location error_location, std::string name)
      : syntax_error(syntax_error_code::FUNCTION_NOT_FOUND,
          std::move(error_location)),
        m_name(std::move(name)) {}

  inline const std::string& function_not_found_syntax_error::get_name() const {
    return m_name;
  }
}

#endif

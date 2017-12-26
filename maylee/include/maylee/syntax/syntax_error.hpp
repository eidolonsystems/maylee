#ifndef MAYLEE_SYNTAX_ERROR_HPP
#define MAYLEE_SYNTAX_ERROR_HPP
#include <stdexcept>
#include <utility>
#include "maylee/lexicon/location.hpp"
#include "maylee/syntax/syntax_error_code.hpp"
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! Indicates a syntax error.
  class syntax_error : public std::runtime_error {
    public:

      //! Constructs a syntax error.
      /*!
        \param code The error code.
        \param location The location in the source code of the error.
      */
      syntax_error(syntax_error_code code, location location);

      //! Returns the error code.
      syntax_error_code get_code() const;

      //! Returns the location of the error.
      const location& get_location() const;

    private:
      syntax_error_code m_code;
      location m_location;
  };

  inline syntax_error::syntax_error(syntax_error_code code, location location)
      : std::runtime_error("Syntax error."),
        m_code(code),
        m_location(std::move(location)) {}

  inline syntax_error_code syntax_error::get_code() const {
    return m_code;
  }

  inline const location& syntax_error::get_location() const {
    return m_location;
  }
}

#endif

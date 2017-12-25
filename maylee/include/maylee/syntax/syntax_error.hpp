#ifndef MAYLEE_SYNTAX_ERROR_HPP
#define MAYLEE_SYNTAX_ERROR_HPP
#include <stdexcept>
#include <utility>
#include "maylee/lexicon/token.hpp"
#include "maylee/syntax/syntax_error_code.hpp"
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! Indicates a syntax error.
  class syntax_error : public std::runtime_error {
    public:

      //! Constructs a syntax error.
      /*!
        \param code The error code.
        \param token The token where the error occurred.
      */
      syntax_error(syntax_error_code code, token token);

      //! Returns the error code.
      syntax_error_code get_code() const;

      //! Returns the token where the error occured.
      const token& get_token() const;

    private:
      syntax_error_code m_code;
      token m_token;
  };

  inline syntax_error::syntax_error(syntax_error_code code, token token)
      : std::runtime_error("Syntax error."),
        m_code(code),
        m_token(std::move(token)) {}

  inline syntax_error_code syntax_error::get_code() const {
    return m_code;
  }

  inline const token& syntax_error::get_token() const {
    return m_token;
  }
}

#endif

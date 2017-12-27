#ifndef MAYLEE_UNMATCHED_BRACKET_SYNTAX_ERROR_HPP
#define MAYLEE_UNMATCHED_BRACKET_SYNTAX_ERROR_HPP
#include "maylee/lexicon/punctuation.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_error.hpp"

namespace maylee {

  //! Indicates one side of a bracket is missing the opposite side
  //! (ie. an open bracket missing a closing bracket or vice versa).
  class unmatched_bracket_syntax_error : public syntax_error {
    public:

      //! Constructs an unmatched bracket syntax error.
      /*!
        \param error_location The location of the unmatched bracket.
        \param bracket The bracket at the error location.
      */
      unmatched_bracket_syntax_error(location error_location,
        punctuation bracket);

      //! Returns the unmatched bracket.
      punctuation get_unmatched_bracket() const;

    private:
      punctuation m_bracket;
  };

  inline unmatched_bracket_syntax_error::unmatched_bracket_syntax_error(
      location error_location, punctuation bracket)
      : syntax_error(syntax_error_code::UNMATCHED_BRACKET,
          std::move(error_location)),
        m_bracket(std::move(bracket)) {}

  inline punctuation unmatched_bracket_syntax_error::
      get_unmatched_bracket() const {
    return m_bracket;
  }
}

#endif

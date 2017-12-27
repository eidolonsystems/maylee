#ifndef MAYLEE_SYNTAX_ERROR_CODE_HPP
#define MAYLEE_SYNTAX_ERROR_CODE_HPP
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! Enumerates all syntax errors.
  enum class syntax_error_code {

    //! An identifier was expected.
    IDENTIFIER_EXPECTED,

    //! An assignment operation was expected.
    ASSIGNMENT_EXPECTED,

    //! An identifier already has a definition.
    IDENTIFIER_ALREADY_DEFINED,

    //! Not enough arguments provided to an operation.
    INSUFFICIENT_ARGUMENTS,

    //! An opening bracket is missing a closing bracket or vice-versa.
    UNMATCHED_BRACKET
  };
}

#endif

#ifndef MAYLEE_SYNTAX_ERROR_CODE_HPP
#define MAYLEE_SYNTAX_ERROR_CODE_HPP
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! Enumerates all syntax errors.
  enum class syntax_error_code {

    //! A new line was expected.
    NEW_LINE_EXPECTED,

    //! An invalid escape character was encountered.
    INVALID_ESCAPE_CHARACTER,

    //! An identifier was expected.
    IDENTIFIER_EXPECTED,

    //! A statement was expected.
    STATEMENT_EXPECTED,

    //! An expression was expected.
    EXPRESSION_EXPECTED,

    //! An assignment operation was expected.
    ASSIGNMENT_EXPECTED,

    //! A colon was expected.
    COLON_EXPECTED,

    //! A comma was expected.
    COMMA_EXPECTED,

    //! An open round bracket was expected.
    OPEN_ROUND_BRACKET_EXPECTED,

    //! A function parameter has already been defined.
    FUNCTION_PARAMETER_ALREADY_DEFINED,

    //! An identifier already has a definition.
    IDENTIFIER_ALREADY_DEFINED,

    //! Not enough arguments provided to an operation.
    INSUFFICIENT_ARGUMENTS,

    //! An opening bracket is missing a closing bracket or vice-versa.
    UNMATCHED_BRACKET,

    //! No function with a specified name was found.
    FUNCTION_NOT_FOUND,

    //! The expression can not be called like a function.
    EXPRESSION_NOT_CALLABLE
  };
}

#endif

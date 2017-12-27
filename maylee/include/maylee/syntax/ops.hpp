#ifndef MAYLEE_OPS_HPP
#define MAYLEE_OPS_HPP
#include <stdexcept>
#include "maylee/lexicon/operation.hpp"
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! Enumerates all supported operators.
  enum class op {

    //! (...
    OPEN_BRACKET,

    //! ...)
    CLOSE_BRACKET,

    //! a + b
    ADD,

    //! a - b
    SUBTRACT,

    //! a * b
    MULTIPLY,

    //! a / b
    DIVIDE
  };

  //! Specifies an operator's associativity.
  enum class associativity {

    //! a + b + c => (a + b) + c
    LEFT_TO_RIGHT,

    //! a = b = c => a = (b = c)
    RIGHT_TO_LEFT
  };

  //! Returns the arity of an operation.
  /*!
    \param o The operation.
    \return The operation's arity.
  */
  constexpr int get_arity(op o) {
    switch(o) {
      case op::OPEN_BRACKET:
        return 1;
      case op::CLOSE_BRACKET:
        return 1;
      case op::ADD:
        return 2;
      case op::SUBTRACT:
        return 2;
      case op::MULTIPLY:
        return 2;
      case op::DIVIDE:
        return 2;
    }
    throw std::runtime_error("Invalid operation specified.");
  }

  //! Returns an operation's precedence.
  /*!
    \param o The operation.
    \return The operation's precedence.
  */
  constexpr int get_precedence(op o) {
    switch(o) {
      case op::OPEN_BRACKET:
        return 2;
      case op::CLOSE_BRACKET:
        return 2;
      case op::ADD:
        return 0;
      case op::SUBTRACT:
        return 0;
      case op::MULTIPLY:
        return 1;
      case op::DIVIDE:
        return 1;
    }
    throw std::runtime_error("Invalid operation specified.");
  }

  //! Returns an operation's associativity.
  /*!
    \param o The operation.
    \return The operation's associativity.
  */
  constexpr associativity get_associativity(op o) {
    switch(o) {
      case op::OPEN_BRACKET:
        return associativity::LEFT_TO_RIGHT;
      case op::CLOSE_BRACKET:
        return associativity::LEFT_TO_RIGHT;
      case op::ADD:
        return associativity::LEFT_TO_RIGHT;
      case op::SUBTRACT:
        return associativity::LEFT_TO_RIGHT;
      case op::MULTIPLY:
        return associativity::LEFT_TO_RIGHT;
      case op::DIVIDE:
        return associativity::LEFT_TO_RIGHT;
    }
    throw std::runtime_error("Invalid operation specified.");
  }

  //! Returns the operation represented by a token.
  /*!
    \param o The token representing the operation.
    \return The operation represented by the token.
  */
  inline op get_op(operation o) {
    switch(o.get_symbol()) {
      case operation::symbol::PLUS:
        return op::ADD;
      case operation::symbol::MINUS:
        return op::SUBTRACT;
      case operation::symbol::TIMES:
        return op::MULTIPLY;
      case operation::symbol::DIVIDE:
        return op::DIVIDE;
    }
    throw std::runtime_error("Invalid operation specified.");
  }
}

#endif

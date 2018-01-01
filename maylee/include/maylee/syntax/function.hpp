#ifndef MAYLEE_FUNCTION_HPP
#define MAYLEE_FUNCTION_HPP
#include <string>
#include <utility>
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/variable.hpp"

namespace maylee {

  //! Represents a function.
  class function : public variable {
    public:

      //! Constructs a function.
      /*!
        \param name The name of the function.
      */
      function(std::string name);
  };

  inline function::function(std::string name)
      : variable(std::move(name)) {}
}

#endif

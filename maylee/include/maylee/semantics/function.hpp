#ifndef MAYLEE_FUNCTION_HPP
#define MAYLEE_FUNCTION_HPP
#include "maylee/semantics/semantics.hpp"
#include "maylee/semantics/variable.hpp"

namespace maylee {

  //! Represents a function.
  class function : public variable {
    public:
      using variable::variable;
  };
}

#endif

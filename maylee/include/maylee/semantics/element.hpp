#ifndef MAYLEE_ELEMENT_HPP
#define MAYLEE_ELEMENT_HPP
#include <memory>
#include <string>
#include "maylee/lexicon/location.hpp"
#include "maylee/semantics/semantics.hpp"

namespace maylee {

  //! Base class for a named element of the language that can be placed in a
  //! scope.
  class element {
    public:

      //! Constructs an element.
      element() = default;

      virtual ~element() = default;

      //! Returns the location where the element was declared.
      virtual const location& get_location() const = 0;

      //! Returns the name of the element.
      virtual const std::string& get_name() const = 0;

    private:
      element(const element&) = delete;
      element& operator =(const element&) = delete;
  };
}

#endif

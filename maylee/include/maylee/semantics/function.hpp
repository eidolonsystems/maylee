#ifndef MAYLEE_FUNCTION_HPP
#define MAYLEE_FUNCTION_HPP
#include "maylee/data_types/function_data_type.hpp"
#include "maylee/semantics/semantics.hpp"
#include "maylee/semantics/variable.hpp"

namespace maylee {

  //! Represents a function.
  class function : public variable {
    public:

      //! Constructs a function.
      /*!
        \param l The location where the function was declared.
        \param name The name of the function.
        \param data_type The function's signature.
      */
      function(location l, std::string name,
        std::shared_ptr<function_data_type> signature);

      //! Returns the function's signature.
      std::shared_ptr<function_data_type> get_signature() const;
  };

  inline function::function(location l, std::string name,
      std::shared_ptr<function_data_type> signature)
      : variable(std::move(l), std::move(name), std::move(signature)) {}

  inline std::shared_ptr<function_data_type> function::get_signature() const {
    return std::static_pointer_cast<function_data_type>(get_data_type());
  }
}

#endif

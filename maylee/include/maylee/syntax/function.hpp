#ifndef MAYLEE_FUNCTION_HPP
#define MAYLEE_FUNCTION_HPP
#include <string>
#include <utility>
#include "maylee/data_types/function_data_type.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/variable.hpp"

namespace maylee {

  //! Represents a function.
  class function : public variable {
    public:

      //! Constructs a function.
      /*!
        \param name The name of the function.
        \param signature The function's data type.
      */
      function(std::string name, std::shared_ptr<function_data_type> signature);

      //! Returns the function's signature.
      std::shared_ptr<function_data_type> get_signature() const;
  };

  inline function::function(std::string name,
      std::shared_ptr<function_data_type> signature)
      : variable(std::move(name), std::move(signature)) {}

  inline std::shared_ptr<function_data_type> function::get_signature() const {
    return std::static_pointer_cast<function_data_type>(get_data_type());
  }
}

#endif

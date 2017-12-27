#ifndef MAYLEE_FUNCTION_HPP
#define MAYLEE_FUNCTION_HPP
#include <string>
#include <utility>
#include "maylee/data_types/function_data_type.hpp"
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! Represents a function.
  class function {
    public:

      //! Constructs a function.
      /*!
        \param name The name of the function.
        \param signature The function's data type.
      */
      function(std::string name, std::shared_ptr<function_data_type> signature);

      //! Returns the name of the function.
      const std::string& get_name() const;

      //! Returns the function's signature.
      const std::shared_ptr<function_data_type>& get_signature() const;

    private:
      std::string m_name;
      std::shared_ptr<function_data_type> m_signature;
  };

  inline function::function(std::string name,
      std::shared_ptr<function_data_type> signature)
      : m_name(std::move(name)),
        m_signature(std::move(signature)) {}

  inline const std::string& function::get_name() const {
    return m_name;
  }

  inline const std::shared_ptr<function_data_type>&
      function::get_signature() const {
    return m_signature;
  }
}

#endif

#ifndef MAYLEE_FUNCTION_DATA_TYPE_HPP
#define MAYLEE_FUNCTION_DATA_TYPE_HPP
#include <memory>
#include <utility>
#include <vector>
#include "maylee/data_types/data_type.hpp"
#include "maylee/data_types/data_types.hpp"

namespace maylee {

  //! The data type used to represent functions.
  class function_data_type : public data_type {
    public:

      //! Stores a single parameter.
      struct parameter {

        //! The name of the parameter.
        std::string m_name;

        //! The parameter's type.
        std::shared_ptr<data_type> m_type;
      };

      //! Constructs a function data type.
      /*!
        \param parameters The function's parameters.
        \param return_type The return type.
      */
      function_data_type(std::vector<parameter> parameters,
        std::shared_ptr<data_type> return_type);

      //! Returns the list of parameters.
      const std::vector<parameter>& get_parameters() const;

      //! Returns the return type.
      const std::shared_ptr<data_type>& get_return_type() const;

      const std::string& get_name() const override final;

    protected:
      bool is_equal(const data_type& rhs) const override final;

    private:
      std::vector<parameter> m_parameters;
      std::shared_ptr<data_type> m_return_type;
      std::string m_name;
  };

  inline function_data_type::function_data_type(
      std::vector<parameter> parameters, std::shared_ptr<data_type> return_type)
      : m_parameters(std::move(parameters)),
        m_return_type(std::move(return_type)) {
    m_name = "(";
    auto is_first = true;
    for(auto& parameter : m_parameters) {
      if(!is_first) {
        m_name += ", ";
      } else {
        is_first = false;
      }
      if(!parameter.m_name.empty()) {
        m_name += parameter.m_name + ": ";
      }
      m_name += parameter.m_type->get_name();
    }
    m_name += ") -> " + m_return_type->get_name();
  }

  inline const std::vector<function_data_type::parameter>&
      function_data_type::get_parameters() const {
    return m_parameters;
  }

  inline const std::shared_ptr<data_type>&
      function_data_type::get_return_type() const {
    return m_return_type;
  }

  inline const std::string& function_data_type::get_name() const {
    return m_name;
  }

  inline bool function_data_type::is_equal(const data_type& rhs) const {
    auto& f = static_cast<const function_data_type&>(rhs);
    if(*m_return_type != *f.get_return_type() ||
        m_parameters.size() != f.get_parameters().size()) {
      return false;
    }
    for(std::size_t i = 0; i < m_parameters.size(); ++i) {
      if(*m_parameters[i].m_type != *f.get_parameters()[i].m_type) {
        return false;
      }
    }
    return true;
  }
}

#endif

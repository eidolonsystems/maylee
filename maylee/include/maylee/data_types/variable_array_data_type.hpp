#ifndef MAYLEE_VARIABLE_ARRAY_DATA_TYPE_HPP
#define MAYLEE_VARIABLE_ARRAY_DATA_TYPE_HPP
#include <memory>
#include "maylee/data_types/data_type.hpp"
#include "maylee/data_types/data_types.hpp"
#include "maylee/data_types/size_data_type.hpp"

namespace maylee {

  //! Represents a variable length array.
  class variable_array_data_type : public data_type {
    public:

      //! Constructs a variable length array data type.
      /*!
        \param type The type stored.
      */
      variable_array_data_type(std::shared_ptr<data_type> type);

      //! Returns the type stored by the array.
      const data_type& get_type() const;

      const std::string& get_name() const override final;

      size get_size() const override final;

    private:
      std::shared_ptr<data_type> m_type;
      std::string m_name;
  };

  inline variable_array_data_type::variable_array_data_type(
      std::shared_ptr<data_type> type)
      : m_type(std::move(type)),
        m_name("[]" + m_type->get_name()) {}

  inline const data_type& variable_array_data_type::get_type() const {
    return *m_type;
  }

  inline const std::string& variable_array_data_type::get_name() const {
    return m_name;
  }

  inline size variable_array_data_type::get_size() const {
    return size_data_type::SIZE;
  }
}

#endif

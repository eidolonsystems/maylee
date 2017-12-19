#ifndef MAYLEE_ARRAY_DATA_TYPE_HPP
#define MAYLEE_ARRAY_DATA_TYPE_HPP
#include <memory>
#include "maylee/data_types/data_type.hpp"
#include "maylee/data_types/data_types.hpp"
#include "maylee/data_types/size_data_type.hpp"

namespace maylee {

  //! Represents a fixed length array.
  class array_data_type : public data_type {
    public:

      //! Constructs an array data type.
      /*!
        \param type The type stored.
        \param length The number of elements.
      */
      array_data_type(std::shared_ptr<data_type> type, size length);

      //! Returns the type stored by the array.
      const data_type& get_type() const;

      //! Returns the number of elements stored.
      size get_length() const;

      const std::string& get_name() const override final;

      size get_size() const override final;

    private:
      std::shared_ptr<data_type> m_type;
      size m_length;
      std::string m_name;
  };

  inline array_data_type::array_data_type(std::shared_ptr<data_type> type,
      size length)
      : m_type(std::move(type)),
        m_length(length),
        m_name("[" + std::to_string(m_length) + "]" + m_type->get_name()) {}

  inline const data_type& array_data_type::get_type() const {
    return *m_type;
  }

  inline size array_data_type::get_length() const {
    return m_length;
  }

  inline const std::string& array_data_type::get_name() const {
    return m_name;
  }

  inline size array_data_type::get_size() const {
    return size_data_type::SIZE() + m_length * m_type->get_size();
  }
}

#endif

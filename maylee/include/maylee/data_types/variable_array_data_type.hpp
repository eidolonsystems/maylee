#ifndef MAYLEE_VARIABLE_ARRAY_DATA_TYPE_HPP
#define MAYLEE_VARIABLE_ARRAY_DATA_TYPE_HPP
#include <memory>
#include "maylee/data_types/data_type.hpp"
#include "maylee/data_types/data_types.hpp"

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
      const std::shared_ptr<data_type>& get_type() const;

      const location& get_location() const override final;

      const std::string& get_name() const override final;

    protected:
      bool is_equal(const data_type& rhs) const override final;

    private:
      std::shared_ptr<data_type> m_type;
      std::string m_name;
  };

  inline variable_array_data_type::variable_array_data_type(
      std::shared_ptr<data_type> type)
      : m_type(std::move(type)),
        m_name("[]" + m_type->get_name()) {}

  inline const std::shared_ptr<data_type>&
      variable_array_data_type::get_type() const {
    return m_type;
  }

  inline const location& variable_array_data_type::get_location() const {
    return location::global();
  }

  inline const std::string& variable_array_data_type::get_name() const {
    return m_name;
  }

  inline bool variable_array_data_type::is_equal(const data_type& rhs) const {
    auto& r = static_cast<const variable_array_data_type&>(rhs);
    return *m_type == *r.get_type();
  }
}

#endif

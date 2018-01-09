#ifndef MAYLEE_STRING_LIT_DATA_TYPE_HPP
#define MAYLEE_STRING_LIT_DATA_TYPE_HPP
#include <memory>
#include "maylee/data_types/data_type.hpp"
#include "maylee/data_types/data_types.hpp"

namespace maylee {

  //! Represents a raw string literal.
  class string_lit_data_type : public data_type {
    public:

      //! Returns an instance of this data type.
      static const std::shared_ptr<string_lit_data_type>& get_instance();

      //! Constructs a string literal data type.
      string_lit_data_type();

      const std::string& get_name() const override final;

    protected:
      bool is_equal(const data_type& rhs) const override final;

    private:
      std::string m_name;
  };

  inline const std::shared_ptr<string_lit_data_type>&
      string_lit_data_type::get_instance() {
    static auto instance = std::make_shared<string_lit_data_type>();
    return instance;
  }

  inline string_lit_data_type::string_lit_data_type()
      : m_name("StringLit") {}

  inline const std::string& string_lit_data_type::get_name() const {
    return m_name;
  }

  inline bool string_lit_data_type::is_equal(const data_type& rhs) const {
    return true;
  }
}

#endif

#ifndef MAYLEE_SIZE_DATA_TYPE_HPP
#define MAYLEE_SIZE_DATA_TYPE_HPP
#include <memory>
#include "maylee/data_types/data_type.hpp"
#include "maylee/data_types/data_types.hpp"

namespace maylee {

  //! Represents a size in bytes.
  class size_data_type : public data_type {
    public:

      //! Returns an instance of this type.
      static const std::shared_ptr<size_data_type>& get_instance();

      //! Constructs a size data type.
      size_data_type() = default;

      const location& get_location() const override final;

      const std::string& get_name() const override final;

    protected:
      bool is_equal(const data_type& rhs) const override final;
  };

  inline const std::shared_ptr<size_data_type>& size_data_type::get_instance() {
    static auto instance = std::make_shared<size_data_type>();
    return instance;
  }

  inline const location& size_data_type::get_location() const {
    return location::global();
  }

  inline const std::string& size_data_type::get_name() const {
    static std::string name = "Size";
    return name;
  }

  inline bool size_data_type::is_equal(const data_type& rhs) const {
    return true;
  }
}

#endif

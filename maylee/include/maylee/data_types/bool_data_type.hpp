#ifndef MAYLEE_BOOL_DATA_TYPE_HPP
#define MAYLEE_BOOL_DATA_TYPE_HPP
#include <memory>
#include "maylee/data_types/data_type.hpp"
#include "maylee/data_types/data_types.hpp"

namespace maylee {

  //! Represents a boolean data type.
  class bool_data_type : public data_type {
    public:

      //! Returns an instance of this type.
      static const std::shared_ptr<bool_data_type>& get_instance();

      //! Constructs a bool data type.
      bool_data_type() = default;

      const std::string& get_name() const override final;

      size get_size() const override final;

    protected:
      bool is_equal(const data_type& rhs) const override final;
  };

  inline const std::shared_ptr<bool_data_type>& bool_data_type::get_instance() {
    static auto instance = std::make_shared<bool_data_type>();
    return instance;
  }

  inline const std::string& bool_data_type::get_name() const {
    static std::string name = "Bool";
    return name;
  }

  inline size bool_data_type::get_size() const {
    return 1;
  }

  inline bool bool_data_type::is_equal(const data_type& rhs) const {
    return true;
  }
}

#endif

#ifndef MAYLEE_BOOL_DATA_TYPE_HPP
#define MAYLEE_BOOL_DATA_TYPE_HPP
#include "maylee/data_types/data_type.hpp"
#include "maylee/data_types/data_types.hpp"

namespace maylee {

  //! Represents a boolean data type.
  class bool_data_type : public data_type {
    public:

      //! Constructs a bool data type.
      bool_data_type() = default;

      const std::string& get_name() const override final;

      int get_size() const override final;
  };

  inline const std::string& bool_data_type::get_name() const {
    static std::string name = "Bool";
    return name;
  }

  inline int bool_data_type::get_size() const {
    return 1;
  }
}

#endif

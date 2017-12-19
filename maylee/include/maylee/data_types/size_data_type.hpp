#ifndef MAYLEE_SIZE_DATA_TYPE_HPP
#define MAYLEE_SIZE_DATA_TYPE_HPP
#include "maylee/data_types/data_type.hpp"
#include "maylee/data_types/data_types.hpp"

namespace maylee {

  //! Represents a size in bytes.
  class size_data_type : public data_type {
    public:

      //! The number of bytes used to represent a size.
      static constexpr int SIZE() { return 8; };

      //! Constructs a size data type.
      size_data_type() = default;

      const std::string& get_name() const override final;

      size get_size() const override final;
  };

  inline const std::string& size_data_type::get_name() const {
    static std::string name = "Size";
    return name;
  }

  inline size size_data_type::get_size() const {
    return SIZE();
  }
}

#endif

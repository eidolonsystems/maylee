#ifndef MAYLEE_CHAR_DATA_TYPE_HPP
#define MAYLEE_CHAR_DATA_TYPE_HPP
#include "maylee/data_types/data_type.hpp"
#include "maylee/data_types/data_types.hpp"

namespace maylee {

  //! Represents a Unicode scalar type.
  class char_data_type : public data_type {
    public:

      //! Constructs a char data type.
      char_data_type() = default;

      const std::string& get_name() const override final;

      int get_size() const override final;
  };

  inline const std::string& char_data_type::get_name() const {
    static std::string name = "Char";
    return name;
  }

  inline int char_data_type::get_size() const {
    return 1;
  }
}

#endif

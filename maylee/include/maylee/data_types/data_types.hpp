#ifndef MAYLEE_DATA_TYPES_HPP
#define MAYLEE_DATA_TYPES_HPP
#include <cstdint>

namespace maylee {
  class array_data_type;
  class bool_data_type;
  class char_data_type;
  class data_type;
  class float_data_type;
  class function_data_type;
  class scalar_data_type;
  class size_data_type;
  class tuple_data_type;
  class union_data_type;
  class variable_array_data_type;

  //! Specifies the type used to represent static sizes.
  using size = std::uint64_t;
}

#endif

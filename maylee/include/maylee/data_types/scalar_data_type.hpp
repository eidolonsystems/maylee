#ifndef MAYLEE_SCALAR_DATA_TYPE_HPP
#define MAYLEE_SCALAR_DATA_TYPE_HPP
#include "maylee/data_types/data_type.hpp"
#include "maylee/data_types/data_types.hpp"

namespace maylee {
  class scalar_data_type : public data_type {
    public:

      int get_size() const;

      bool is_unsigned() const;
  };
}

#endif

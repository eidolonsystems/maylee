#ifndef MAYLEE_DATA_TYPE_HPP
#define MAYLEE_DATA_TYPE_HPP
#include <string>
#include "maylee/data_types/data_types.hpp"

namespace maylee {

  //! The base class for a data type.
  class data_type {
    public:

      //! Constructs a data type.
      data_type() = default;

      virtual ~data_type() = default;

      //! Returns the name of the data type.
      virtual const std::string& get_name() const = 0;

      //! Returns the size in bytes of the data type.
      virtual int get_size() const = 0;

    private:
      data_type(const data_type&) = delete;
      data_type& operator =(const data_type&) = delete;
  };
}

#endif

#ifndef MAYLEE_DATA_TYPE_HPP
#define MAYLEE_DATA_TYPE_HPP
#include <ostream>
#include <string>
#include "maylee/data_types/data_types.hpp"

namespace maylee {

  //! The base class for a data type.
  class data_type {
    public:
      virtual ~data_type() = default;

      //! Returns the name of the data type.
      virtual const std::string& get_name() const = 0;

      //! Returns the size in bytes of the data type.
      virtual size get_size() const = 0;

      //! Tests if two data types are identical.
      /*!
        \param rhs The right hand side to test.
        \return <code>true</code> iff the two data types are identical.
      */
      bool operator ==(const data_type& rhs) const;

      //! Tests if two data types are not identical.
      /*!
        \param rhs The right hand side to test.
        \return <code>true</code> iff the two data types are not identical.
      */
      bool operator !=(const data_type& rhs) const;

    protected:

      //! Constructs a data type.
      data_type() = default;

      //! Tests if two data types are identical.
      /*!
        \param rhs The right hand side to test, guaranteed to not be the same
                   object as <i>this</i> and has the same type as <i>this</i>.
        \return <code>true</code> iff the two data types are identical.
      */
      virtual bool is_equal(const data_type& rhs) const = 0;

    private:
      data_type(const data_type&) = delete;
      data_type& operator =(const data_type&) = delete;
  };

  inline std::ostream& operator <<(std::ostream& out, const data_type& value) {
    return out << value.get_name();
  }

  inline bool data_type::operator ==(const data_type& rhs) const {
    if(this == &rhs) {
      return true;
    } else if(typeid(*this) != typeid(rhs)) {
      return false;
    }
    return is_equal(rhs);
  }

  inline bool data_type::operator !=(const data_type& rhs) const {
    return !(*this == rhs);
  }
}

#endif

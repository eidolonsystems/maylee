#ifndef MAYLEE_SCALAR_DATA_TYPE_HPP
#define MAYLEE_SCALAR_DATA_TYPE_HPP
#include <memory>
#include <stdexcept>
#include "maylee/data_types/data_type.hpp"
#include "maylee/data_types/data_types.hpp"

namespace maylee {

  //! Represents a scalar primitive data type.
  class scalar_data_type : public data_type {
    public:

      //! The list of scalar types supported.
      enum class type {

        //! 8-bit signed integer.
        SBYTE,

        //! 16-bit signed integer.
        SHORT,

        //! 32-bit signed integer.
        INT,

        //! 64-bit signed integer.
        LONG,

        //! 8-bit unsigned integer.
        BYTE,

        //! 16-bit unsigned integer.
        USHORT,

        //! 32-bit unsigned integer.
        UINT,

        //! 64-bit unsigned integer.
        ULONG,
      };

      //! Returns an instance of SBYTE.
      static const std::shared_ptr<scalar_data_type>& get_sbyte();

      //! Returns an instance of SHORT.
      static const std::shared_ptr<scalar_data_type>& get_short();

      //! Returns an instance of INT.
      static const std::shared_ptr<scalar_data_type>& get_int();

      //! Returns an instance of LONG.
      static const std::shared_ptr<scalar_data_type>& get_long();

      //! Returns an instance of BYTE.
      static const std::shared_ptr<scalar_data_type>& get_byte();

      //! Returns an instance of USHORT.
      static const std::shared_ptr<scalar_data_type>& get_ushort();

      //! Returns an instance of UINT.
      static const std::shared_ptr<scalar_data_type>& get_uint();

      //! Returns an instance of ULONG.
      static const std::shared_ptr<scalar_data_type>& get_ulong();

      //! Returns an instance of this type.
      /*!
        \param t The type of scalar to get.
      */
      static const std::shared_ptr<scalar_data_type>& get_instance(type t);

      //! Constructs a scalar data type.
      /*!
        \param type The type of scalar.
      */
      scalar_data_type(type type);

      //! Returns the type of scalar represented.
      type get_type() const;

      //! Returns <code>true</code> iff the scalar is unsigned.
      bool is_unsigned() const;

      const std::string& get_name() const override final;

    protected:
      bool is_equal(const data_type& rhs) const override final;

    private:
      type m_type;
  };

  inline const std::shared_ptr<scalar_data_type>&
      scalar_data_type::get_sbyte() {
    static auto value = std::make_shared<scalar_data_type>(type::SBYTE);
    return value;
  }

  inline const std::shared_ptr<scalar_data_type>&
      scalar_data_type::get_short() {
    static auto value = std::make_shared<scalar_data_type>(type::SHORT);
    return value;
  }

  inline const std::shared_ptr<scalar_data_type>& scalar_data_type::get_int() {
    static auto value = std::make_shared<scalar_data_type>(type::INT);
    return value;
  }

  inline const std::shared_ptr<scalar_data_type>& scalar_data_type::get_long() {
    static auto value = std::make_shared<scalar_data_type>(type::LONG);
    return value;
  }

  inline const std::shared_ptr<scalar_data_type>& scalar_data_type::get_byte() {
    static auto value = std::make_shared<scalar_data_type>(type::BYTE);
    return value;
  }

  inline const std::shared_ptr<scalar_data_type>&
      scalar_data_type::get_ushort() {
    static auto value = std::make_shared<scalar_data_type>(type::USHORT);
    return value;
  }

  inline const std::shared_ptr<scalar_data_type>&
      scalar_data_type::get_uint() {
    static auto value = std::make_shared<scalar_data_type>(type::UINT);
    return value;
  }

  inline const std::shared_ptr<scalar_data_type>&
      scalar_data_type::get_ulong() {
    static auto value = std::make_shared<scalar_data_type>(type::ULONG);
    return value;
  }

  inline const std::shared_ptr<scalar_data_type>&
      scalar_data_type::get_instance(type t) {
    switch(t) {
      case type::SBYTE:
        return get_sbyte();
      case type::SHORT:
        return get_short();
      case type::INT:
        return get_int();
      case type::LONG:
        return get_long();
      case type::BYTE:
        return get_byte();
      case type::USHORT:
        return get_ushort();
      case type::UINT:
        return get_uint();
      case type::ULONG:
        return get_ulong();
      default:
        throw std::invalid_argument("Invalid scalar type.");
    }
  }

  inline scalar_data_type::scalar_data_type(type type)
      : m_type(type) {}

  inline scalar_data_type::type scalar_data_type::get_type() const {
    return m_type;
  }

  inline bool scalar_data_type::is_unsigned() const {
    return m_type >= type::BYTE;
  }

  inline const std::string& scalar_data_type::get_name() const {
    switch(m_type) {
      case type::SBYTE:
        {
          static std::string value = "SByte";
          return value;
        }
      case type::SHORT:
        {
          static std::string value = "Short";
          return value;
        }
      case type::INT:
        {
          static std::string value = "Int";
          return value;
        }
      case type::LONG:
        {
          static std::string value = "Long";
          return value;
        }
      case type::BYTE:
        {
          static std::string value = "Byte";
          return value;
        }
      case type::USHORT:
        {
          static std::string value = "UShort";
          return value;
        }
      case type::UINT:
        {
          static std::string value = "UInt";
          return value;
        }
      case type::ULONG:
        {
          static std::string value = "ULong";
          return value;
        }
      default:
        throw std::invalid_argument("Invalid scalar type.");
    }
  }

  inline bool scalar_data_type::is_equal(const data_type& rhs) const {
    auto& r = static_cast<const scalar_data_type&>(rhs);
    return m_type == r.get_type();
  }
}

#endif

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
        INT8,

        //! 16-bit signed integer.
        INT16,

        //! 32-bit signed integer.
        INT32,

        //! 64-bit signed integer.
        INT64,

        //! 8-bit unsigned integer.
        UINT8,

        //! 16-bit unsigned integer.
        UINT16,

        //! 32-bit unsigned integer.
        UINT32,

        //! 64-bit unsigned integer.
        UINT64,
      };

      //! Returns an instance of INT8.
      static const std::shared_ptr<scalar_data_type>& get_int8();

      //! Returns an instance of INT16.
      static const std::shared_ptr<scalar_data_type>& get_int16();

      //! Returns an instance of INT32.
      static const std::shared_ptr<scalar_data_type>& get_int32();

      //! Returns an instance of INT64.
      static const std::shared_ptr<scalar_data_type>& get_int64();

      //! Returns an instance of UINT8.
      static const std::shared_ptr<scalar_data_type>& get_uint8();

      //! Returns an instance of UINT16.
      static const std::shared_ptr<scalar_data_type>& get_uint16();

      //! Returns an instance of UINT32.
      static const std::shared_ptr<scalar_data_type>& get_uint32();

      //! Returns an instance of UINT64.
      static const std::shared_ptr<scalar_data_type>& get_uint64();

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

      size get_size() const override final;

    protected:
      bool is_equal(const data_type& rhs) const override final;

    private:
      type m_type;
  };

  inline const std::shared_ptr<scalar_data_type>&
      scalar_data_type::get_int8() {
    static auto value = std::make_shared<scalar_data_type>(type::INT8);
    return value;
  }

  inline const std::shared_ptr<scalar_data_type>&
      scalar_data_type::get_int16() {
    static auto value = std::make_shared<scalar_data_type>(type::INT16);
    return value;
  }

  inline const std::shared_ptr<scalar_data_type>&
      scalar_data_type::get_int32() {
    static auto value = std::make_shared<scalar_data_type>(type::INT32);
    return value;
  }

  inline const std::shared_ptr<scalar_data_type>&
      scalar_data_type::get_int64() {
    static auto value = std::make_shared<scalar_data_type>(type::INT64);
    return value;
  }

  inline const std::shared_ptr<scalar_data_type>&
      scalar_data_type::get_uint8() {
    static auto value = std::make_shared<scalar_data_type>(type::UINT8);
    return value;
  }

  inline const std::shared_ptr<scalar_data_type>&
      scalar_data_type::get_uint16() {
    static auto value = std::make_shared<scalar_data_type>(type::UINT16);
    return value;
  }

  inline const std::shared_ptr<scalar_data_type>&
      scalar_data_type::get_uint32() {
    static auto value = std::make_shared<scalar_data_type>(type::UINT32);
    return value;
  }

  inline const std::shared_ptr<scalar_data_type>&
      scalar_data_type::get_uint64() {
    static auto value = std::make_shared<scalar_data_type>(type::UINT64);
    return value;
  }

  inline const std::shared_ptr<scalar_data_type>&
      scalar_data_type::get_instance(type t) {
    switch(t) {
      case type::INT8:
        return get_int8();
      case type::INT16:
        return get_int16();
      case type::INT32:
        return get_int32();
      case type::INT64:
        return get_int64();
      case type::UINT8:
        return get_uint8();
      case type::UINT16:
        return get_uint16();
      case type::UINT32:
        return get_uint32();
      case type::UINT64:
        return get_uint64();
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
    return m_type >= type::UINT8;
  }

  inline const std::string& scalar_data_type::get_name() const {
    switch(m_type) {
      case type::INT8:
        {
          static std::string value = "Int8";
          return value;
        }
      case type::INT16:
        {
          static std::string value = "Int16";
          return value;
        }
      case type::INT32:
        {
          static std::string value = "Int32";
          return value;
        }
      case type::INT64:
        {
          static std::string value = "Int64";
          return value;
        }
      case type::UINT8:
        {
          static std::string value = "UInt8";
          return value;
        }
      case type::UINT16:
        {
          static std::string value = "UInt16";
          return value;
        }
      case type::UINT32:
        {
          static std::string value = "UInt32";
          return value;
        }
      case type::UINT64:
        {
          static std::string value = "UInt64";
          return value;
        }
      default:
        throw std::invalid_argument("Invalid scalar type.");
    }
  }

  inline size scalar_data_type::get_size() const {
    switch(m_type) {
      case type::INT8:
        return 1;
      case type::INT16:
        return 2;
      case type::INT32:
        return 4;
      case type::INT64:
        return 8;
      case type::UINT8:
        return 1;
      case type::UINT16:
        return 2;
      case type::UINT32:
        return 4;
      case type::UINT64:
        return 8;
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

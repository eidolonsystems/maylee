#ifndef MAYLEE_FLOAT_DATA_TYPE_HPP
#define MAYLEE_FLOAT_DATA_TYPE_HPP
#include <memory>
#include <stdexcept>
#include "maylee/data_types/data_type.hpp"
#include "maylee/data_types/data_types.hpp"

namespace maylee {

  //! Represents an IEEE 754 binary floating point primitive data type.
  class float_data_type : public data_type {
    public:

      //! The list of floating point types supported.
      enum class type {

        //! 32-bit single precision floating point.
        FLOAT,

        //! 64-bit double precision floating point.
        DOUBLE
      };

      //! Returns an instance of FLOAT.
      static const std::shared_ptr<float_data_type>& get_float();

      //! Returns an instance of DOUBLE.
      static const std::shared_ptr<float_data_type>& get_double();

      //! Returns an instance of this type.
      /*!
        \param t The type of floating point to get.
      */
      static const std::shared_ptr<float_data_type>& get_instance(type t);

      //! Constructs a float data type.
      /*!
        \param type The type of float.
      */
      float_data_type(type type);

      //! Returns the type of float represented.
      type get_type() const;

      const std::string& get_name() const override final;

    protected:
      bool is_equal(const data_type& rhs) const override final;

    private:
      type m_type;
  };

  inline const std::shared_ptr<float_data_type>&
      float_data_type::get_float() {
    static auto value = std::make_shared<float_data_type>(type::FLOAT);
    return value;
  }

  inline const std::shared_ptr<float_data_type>&
      float_data_type::get_double() {
    static auto value = std::make_shared<float_data_type>(type::DOUBLE);
    return value;
  }

  inline const std::shared_ptr<float_data_type>& float_data_type::get_instance(
      type t) {
    switch(t) {
      case type::FLOAT:
        return get_float();
      case type::DOUBLE:
        return get_double();
      default:
        throw std::invalid_argument("Invalid float type.");
    }
  }

  inline float_data_type::float_data_type(type type)
      : m_type(type) {}

  inline float_data_type::type float_data_type::get_type() const {
    return m_type;
  }

  inline const std::string& float_data_type::get_name() const {
    switch(m_type) {
      case type::FLOAT:
        {
          static std::string value = "Float";
          return value;
        }
      case type::DOUBLE:
        {
          static std::string value = "Double";
          return value;
        }
      default:
        throw std::invalid_argument("Invalid float type.");
    }
  }

  inline bool float_data_type::is_equal(const data_type& rhs) const {
    auto& r = static_cast<const float_data_type&>(rhs);
    return m_type == r.get_type();
  }
}

#endif

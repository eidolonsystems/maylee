#ifndef MAYLEE_LITERAL_HPP
#define MAYLEE_LITERAL_HPP
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/data_types/data_type.hpp"
#include "maylee/data_types/float_data_type.hpp"
#include "maylee/data_types/scalar_data_type.hpp"
#include "maylee/lexicon/keyword.hpp"
#include "maylee/lexicon/lexicon.hpp"
#include "maylee/lexicon/operation.hpp"
#include "maylee/lexicon/punctuation.hpp"

namespace maylee {

  //! Stores a literal token.
  class literal {
    public:

      //! Constructs a literal.
      /*!
        \param value The string representation of the value.
        \param type The literal value's data type.
      */
      literal(std::string value, std::shared_ptr<data_type> type);

      //! Returns the string representation of the value.
      const std::string& get_value() const;

      //! Returns the literal value's data type.
      const std::shared_ptr<data_type>& get_type() const;

    private:
      std::string m_value;
      std::shared_ptr<data_type> m_type;
  };

  //! Parses a literal.
  /*!
    \param cursor A pointer to the first character to parse, this pointer will
           be adjusted to one past the last character that was parsed.
    \param size The number of characters available, this number will be adjusted
           by the number of characters parsed.
    \return The literal that was parsed.
  */
  inline std::optional<literal> parse_literal(const char*& cursor,
      std::size_t& size) {
    auto is_separator =
      [] (char c) {
        return std::isalnum(c) || std::isspace(c) || c == '_' ||
          is_punctuation(c) || is_operation_delimiter(c);
      };
    auto parse_decimal =
      [] (const char*& cursor, std::size_t& size) {
        while(size != 0 && std::isdigit(*cursor)) {
          ++cursor;
          --size;
        }
      };
    if(size == 0) {
      return std::nullopt;
    }
    if(prefix_match(cursor, size, "true")) {
      return literal("true", bool_data_type::get_instance());
    }
    if(prefix_match(cursor, size, "false")) {
      return literal("false", bool_data_type::get_instance());
    }
    auto c = cursor;
    auto s = size;
    if(std::isdigit(*c)) {
      parse_decimal(c, s);
      if(s == 0) {
        return std::nullopt;
      }
      if(*c != '.') {
        if(!is_separator(*c)) {
          return std::nullopt;
        }
        auto value = std::string(cursor, c - cursor);
        cursor = c;
        size = s;
        return literal(std::move(value),
          scalar_data_type::get_instance(scalar_data_type::type::INT32));
      } else {
        ++c;
        --s;
        parse_decimal(c, s);
        if(s == 0) {
          return std::nullopt;
        }
        if(!is_separator(*c)) {
          return std::nullopt;
        }
        auto value = std::string(cursor, c - cursor);
        cursor = c;
        size = s;
        return literal(std::move(value),
          float_data_type::get_instance(float_data_type::type::FLOAT64));
      }
    }
    return std::nullopt;
  }

  inline std::ostream& operator <<(std::ostream& out, const literal& value) {
    return out << value.get_value();
  }

  inline bool operator ==(const literal& lhs, const literal& rhs) {
    return lhs.get_value() == rhs.get_value() &&
      *lhs.get_type() == *rhs.get_type();
  }

  inline bool operator !=(const literal& lhs, const literal& rhs) {
    return !(lhs == rhs);
  }

  inline literal::literal(std::string value, std::shared_ptr<data_type> type)
      : m_value(std::move(value)),
        m_type(std::move(type)) {}

  inline const std::string& literal::get_value() const {
    return m_value;
  }

  inline const std::shared_ptr<data_type>& literal::get_type() const {
    return m_type;
  }
}

#endif

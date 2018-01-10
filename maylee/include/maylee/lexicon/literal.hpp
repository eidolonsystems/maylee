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
#include "maylee/data_types/string_lit_data_type.hpp"
#include "maylee/lexicon/bracket.hpp"
#include "maylee/lexicon/keyword.hpp"
#include "maylee/lexicon/lexical_iterator.hpp"
#include "maylee/lexicon/lexicon.hpp"
#include "maylee/lexicon/operation.hpp"
#include "maylee/lexicon/punctuation.hpp"
#include "maylee/syntax/syntax_error.hpp"

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

  //! Returns the escape character corresponding to a value.
  /*!
    \param c The escape character to translate.
    \return The translated escape character.
  */
  inline std::optional<char> translate_escape_character(char c) {
    if(c == '\\') {
      return '\\';
    } else if(c == 'n') {
      return '\n';
    } else if(c == 'r') {
      return '\r';
    } else if(c == '"') {
      return '"';
    } else if(c == 'b') {
      return '\b';
    } else if(c == 'f') {
      return '\f';
    } else if(c == 't') {
      return '\t';
    }
    return std::nullopt;
  }

  //! Parses a string literal.
  /*!
    \param cursor An iterator to the first character to parse, this iterator
           will be adjusted to one past the last character that was parsed.
    \return The string literal that was parsed.
  */
  inline std::optional<literal> parse_string_literal(
      lexical_iterator& cursor) {
    if(cursor.is_empty() || *cursor != '"') {
      return std::nullopt;
    }
    auto c = cursor + 1;
    std::string value;
    while(true) {
      if(c.is_empty()) {
        return std::nullopt;
      }
      if(*c == '"') {
        break;
      }
      if(*c == '\\') {
        ++c;
        if(c.is_empty()) {
          return std::nullopt;
        }
        auto escape = translate_escape_character(*c);
        if(escape.has_value()) {
          value += *escape;
        } else {
          throw syntax_error(syntax_error_code::INVALID_ESCAPE_CHARACTER,
            c.get_location());
        }
      } else {
        value += *c;
      }
      ++c;
    }
    ++c;
    cursor = c;
    return literal(value, string_lit_data_type::get_instance());
  }

  //! Parses a literal.
  /*!
    \param cursor An iterator to the first character to parse, this iterator
           will be adjusted to one past the last character that was parsed.
    \return The literal that was parsed.
  */
  inline std::optional<literal> parse_literal(lexical_iterator& cursor) {
    auto is_separator =
      [] (char c) {
        return std::isspace(c) || is_punctuation(c) || is_bracket(c) ||
          is_operation_delimiter(c) || c == '\0';
      };
    auto parse_decimal =
      [] (lexical_iterator& cursor) {
        while(!cursor.is_empty() && std::isdigit(*cursor)) {
          ++cursor;
        }
      };
    if(cursor.is_empty()) {
      return std::nullopt;
    }
    if(prefix_match(cursor, "true")) {
      return literal("true", bool_data_type::get_instance());
    }
    if(prefix_match(cursor, "false")) {
      return literal("false", bool_data_type::get_instance());
    }
    if(auto l = parse_string_literal(cursor)) {
      return l;
    }
    auto c = cursor;
    if(std::isdigit(*c)) {
      parse_decimal(c);
      if(c.is_empty()) {
        return std::nullopt;
      }
      if(*c != '.') {
        if(!is_separator(*c)) {
          return std::nullopt;
        }
        auto value = std::string(&*cursor, c - cursor);
        cursor = c;
        return literal(std::move(value), scalar_data_type::get_int());
      } else {
        ++c;
        parse_decimal(c);
        if(c.is_empty()) {
          return std::nullopt;
        }
        if(!is_separator(*c)) {
          return std::nullopt;
        }
        auto value = std::string(&*cursor, c - cursor);
        cursor = c;
        return literal(std::move(value),
          float_data_type::get_instance(float_data_type::type::DOUBLE));
      }
    }
    return std::nullopt;
  }

  //! Parses a literal from a string.
  /*!
    \param source The string to parse.
    \return The literal that was parsed.
  */
  inline auto parse_literal(const std::string_view& source) {
    return maylee::parse_literal(
      lexical_iterator(source.data(), source.size() + 1));
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

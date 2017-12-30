#ifndef MAYLEE_PUNCTUATION_HPP
#define MAYLEE_PUNCTUATION_HPP
#include <optional>
#include <ostream>
#include <stdexcept>
#include "maylee/lexicon/lexical_iterator.hpp"
#include "maylee/lexicon/lexicon.hpp"

namespace maylee {

  //! Stores a punctuation mark.
  class punctuation {
    public:

      //! The list of punctuation marks.
      enum class mark {

        //! '('
        OPEN_BRACKET,

        //! ')'
        CLOSE_BRACKET,

        //! ':'
        COLON,

        //! ','
        COMMA,

        //! '.'
        DOT,

        //! '|'
        BAR
      };

      //! Constructs a punctuation.
      /*!
        \param mark The mark to represent.
      */
      punctuation(mark mark);

      //! Returns the punctuation mark represented.
      mark get_mark() const;

    private:
      mark m_mark;
  };

  //! Returns <code>true</code> iff a character represents a punctuation.
  /*!
    \param c The character to test.
  */
  inline bool is_punctuation(char c) {
    return c == '(' || c == ')' || c == ':' || c == ',' || c == '.' || c == '|';
  }

  //! Parses a punctuation.
  /*!
    \param cursor An iterator to the first character to parse, this iterator
           will be adjusted to one past the last character that was parsed.
    \return The punctuation that was parsed.
  */
  inline std::optional<punctuation> parse_punctuation(
      lexical_iterator& cursor) {
    if(!cursor.is_empty()) {
      if(*cursor == '(') {
        ++cursor;
        return punctuation::mark::OPEN_BRACKET;
      } else if(*cursor == ')') {
        ++cursor;
        return punctuation::mark::CLOSE_BRACKET;
      } else if(*cursor == ':') {
        ++cursor;
        return punctuation::mark::COLON;
      } else if(*cursor == ',') {
        ++cursor;
        return punctuation::mark::COMMA;
      } else if(*cursor == '.') {
        ++cursor;
        return punctuation::mark::DOT;
      } else if(*cursor == '|') {
        ++cursor;
        return punctuation::mark::BAR;
      }
    }
    return std::nullopt;
  }

  //! Parses a punctuation from a string.
  /*!
    \param source The string to parse.
    \return The punctuation that was parsed.
  */
  inline auto parse_punctuation(const std::string_view& source) {
    return maylee::parse_punctuation(
      lexical_iterator(source.data(), source.size() + 1));
  }

  inline std::ostream& operator <<(std::ostream& out,
      const punctuation& value) {
    switch(value.get_mark()) {
      case punctuation::mark::OPEN_BRACKET:
        return out << '(';
      case punctuation::mark::CLOSE_BRACKET:
        return out << ')';
      case punctuation::mark::COLON:
        return out << ':';
      case punctuation::mark::COMMA:
        return out << ',';
      case punctuation::mark::DOT:
        return out << '.';
      case punctuation::mark::BAR:
        return out << '|';
      default:
        throw std::runtime_error("Invalid punctuation mark.");
    }
  }

  inline bool operator ==(const punctuation& lhs, const punctuation& rhs) {
    return lhs.get_mark() == rhs.get_mark();
  }

  inline bool operator !=(const punctuation& lhs, const punctuation& rhs) {
    return !(lhs == rhs);
  }

  inline punctuation::punctuation(mark mark)
      : m_mark(mark) {}

  inline punctuation::mark punctuation::get_mark() const {
    return m_mark;
  }
}

#endif

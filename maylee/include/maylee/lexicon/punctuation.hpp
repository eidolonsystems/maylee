#ifndef MAYLEE_PUNCTUATION_HPP
#define MAYLEE_PUNCTUATION_HPP
#include <optional>
#include <ostream>
#include <stdexcept>
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
    \param cursor A pointer to the first character to parse, this pointer will
           be adjusted to one past the last character that was parsed.
    \param size The number of characters available, this number will be adjusted
           by the number of characters parsed.
    \return The punctuation that was parsed.
  */
  inline std::optional<punctuation> parse_punctuation(const char*& cursor,
      std::size_t& size) {
    if(size >= 1) {
      if(*cursor == '(') {
        ++cursor;
        --size;
        return punctuation::mark::OPEN_BRACKET;
      } else if(*cursor == ')') {
        ++cursor;
        --size;
        return punctuation::mark::CLOSE_BRACKET;
      } else if(*cursor == ':') {
        ++cursor;
        --size;
        return punctuation::mark::COLON;
      } else if(*cursor == ',') {
        ++cursor;
        --size;
        return punctuation::mark::COMMA;
      } else if(*cursor == '.') {
        ++cursor;
        --size;
        return punctuation::mark::DOT;
      } else if(*cursor == '|') {
        ++cursor;
        --size;
        return punctuation::mark::BAR;
      }
    }
    return std::nullopt;
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

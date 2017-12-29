#ifndef MAYLEE_KEYWORD_HPP
#define MAYLEE_KEYWORD_HPP
#include <algorithm>
#include <cctype>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <string_view>
#include "maylee/lexicon/lexicon.hpp"

namespace maylee {

  //! Stores a keyword token.
  class keyword {
    public:

      //! The list of keywords.
      enum class word {

        //! def
        DEFINE,

        //! let
        LET,

        //! if
        IF,

        //! else
        ELSE,

        //! else if
        ELSE_IF,

        //! end
        END,

        //! return
        RETURN,

        //! _
        IGNORE,
      };

      //! Constructs a keyword.
      /*!
        \param word The word to represent.
      */
      keyword(word word);

      //! Returns the word represented.
      word get_word() const;

    private:
      word m_word;
  };

  //! Checks if a string prefix matches a string literal.
  template<std::size_t N>
  inline bool prefix_match(const char*& lhs, std::size_t& size,
      const char (&rhs)[N]) {
    if(size >= N && std::equal(lhs, lhs + (N - 1), rhs) &&
        !std::isalnum(lhs[N - 1]) && lhs[N - 1] != '_') {
      lhs += N - 1;
      size -= N - 1;
      return true;
    }
    return false;
  }

  //! Parses a keyword.
  /*!
    \param cursor A pointer to the first character to parse, this pointer will
           be adjusted to one past the last character that was parsed.
    \param size The number of characters available, this number will be adjusted
           by the number of characters parsed.
    \return The keyword that was parsed.
  */
  inline std::optional<keyword> parse_keyword(const char*& cursor,
      std::size_t& size) {
    if(prefix_match(cursor, size, "def")) {
      return keyword::word::DEFINE;
    } else if(prefix_match(cursor, size, "let")) {
      return keyword::word::LET;
    } else if(prefix_match(cursor, size, "if")) {
      return keyword::word::IF;
    } else if(prefix_match(cursor, size, "end")) {
      return keyword::word::END;
    } else if(prefix_match(cursor, size, "return")) {
      return keyword::word::RETURN;
    } else if(prefix_match(cursor, size, "_")) {
      return keyword::word::IGNORE;
    }
    auto c = cursor;
    auto s = size;
    if(prefix_match(c, s, "else")) {
      while(s != 0 && std::isspace(*c)) {
        ++c;
        --s;
      }
      if(s == 0) {
        return std::nullopt;
      } else if(prefix_match(c, s, "if")) {
        cursor = c;
        size = s;
        return keyword::word::ELSE_IF;
      } else if(*c != 'i' || s > 1 && c[1] != 'f' || s > 2) {
        return keyword::word::ELSE;
      }
    }
    return std::nullopt;
  }

  inline std::ostream& operator <<(std::ostream& out, const keyword& value) {
    switch(value.get_word()) {
      case keyword::word::DEFINE:
        return out << "def";
      case keyword::word::LET:
        return out << "let";
      case keyword::word::IF:
        return out << "if";
      case keyword::word::ELSE:
        return out << "else";
      case keyword::word::ELSE_IF:
        return out << "else if";
      case keyword::word::END:
        return out << "end";
      case keyword::word::RETURN:
        return out << "return";
      case keyword::word::IGNORE:
        return out << "_";
      default:
        throw std::runtime_error("Invalid keyword.");
    }
  }

  inline bool operator ==(const keyword& lhs, const keyword& rhs) {
    return lhs.get_word() == rhs.get_word();
  }

  inline bool operator !=(const keyword& lhs, const keyword& rhs) {
    return !(lhs == rhs);
  }

  inline keyword::keyword(word word)
      : m_word(word) {}

  inline keyword::word keyword::get_word() const {
    return m_word;
  }
}

#endif

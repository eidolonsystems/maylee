#ifndef MAYLEE_IDENTIFIER_HPP
#define MAYLEE_IDENTIFIER_HPP
#include <cctype>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include "maylee/lexicon/lexicon.hpp"

namespace maylee {

  //! Stores an identifier.
  class identifier {
    public:

      //! Constructs an identifier.
      /*!
        \param symbol The identifier's symbol.
      */
      identifier(std::string symbol);

      //! Returns the symbol.
      const std::string& get_symbol() const;

    private:
      std::shared_ptr<std::string> m_symbol;
  };

  //! Parses an identifier.
  /*!
    \param cursor A pointer to the first character to parse, this pointer will
           be adjusted to one past the last character that was parsed.
    \param size The number of characters available, this number will be adjusted
           by the number of characters parsed.
    \return The identifier that was parsed.
  */
  inline std::optional<identifier> parse_identifier(const char*& cursor,
      std::size_t& size) {
    if(size == 0) {
      return std::nullopt;
    }
    auto c = cursor;
    auto s = size;
    if(!std::isalpha(*cursor) && *cursor != '_') {
      return std::nullopt;
    }
    ++c;
    --s;
    while(s != 0) {
      if(!std::isalnum(*c) && *c != '_') {
        std::string identifier(cursor, (c - cursor));
        cursor = c;
        size = s;
        return identifier;
      }
      ++c;
      --s;
    }
    return std::nullopt;
  }

  inline std::ostream& operator <<(std::ostream& out, const identifier& value) {
    return out << value.get_symbol();
  }

  inline bool operator ==(const identifier& lhs, const identifier& rhs) {
    return lhs.get_symbol() == rhs.get_symbol();
  }

  inline bool operator !=(const identifier& lhs, const identifier& rhs) {
    return !(lhs == rhs);
  }

  inline identifier::identifier(std::string symbol)
      : m_symbol(std::make_shared<std::string>(std::move(symbol))) {}

  inline const std::string& identifier::get_symbol() const {
    return *m_symbol;
  }
}

#endif

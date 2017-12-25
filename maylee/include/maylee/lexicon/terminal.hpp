#ifndef MAYLEE_TERMINAL_HPP
#define MAYLEE_TERMINAL_HPP
#include <optional>
#include <ostream>
#include "maylee/lexicon/lexicon.hpp"

namespace maylee {

  //! A token that represents the end of the source code.
  class terminal {
    public:

      //! Constructs a terminal.
      terminal() = default;
  };

  //! Parses a terminal token.
  /*!
    \param cursor A pointer to the first character to parse, this pointer will
           be adjusted to one past the last character that was parsed.
    \param size The number of characters available, this number will be adjusted
           by the number of characters parsed.
    \return The terminal token that was parsed.
  */
  inline std::optional<terminal> parse_terminal(const char*& cursor,
      std::size_t remaining_size) {
    if(remaining_size != 0 && *cursor == '\0') {
      ++cursor;
      --remaining_size;
      return terminal();
    }
    return std::nullopt;
  }

  inline std::ostream& operator <<(std::ostream& out, const terminal& value) {
    return out;
  }

  inline bool operator ==(const terminal& lhs, const terminal& rhs) {
    return true;
  }

  inline bool operator !=(const terminal& lhs, const terminal& rhs) {
    return !(lhs == rhs);
  }
}

#endif

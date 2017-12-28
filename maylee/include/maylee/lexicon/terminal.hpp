#ifndef MAYLEE_TERMINAL_HPP
#define MAYLEE_TERMINAL_HPP
#include <optional>
#include <ostream>
#include "maylee/lexicon/lexicon.hpp"

namespace maylee {

  //! A token that represents the end of a statement.
  class terminal {
    public:

      // Enumerates the types of terminal tokens.
      enum class type {

        //! The token represents a new line.
        new_line,

        //! The token marks the end of the file.
        end_of_file
      };

      //! Constructs a terminal.
      /*!
        \param type The type of terminal.
      */
      terminal(type type);

      //! Returns the type of terminal.
      type get_type() const;

    private:
      type m_type;
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
    if(remaining_size != 0) {
      if(*cursor == '\0') {
        ++cursor;
        --remaining_size;
        return terminal(terminal::type::end_of_file);
      } else if(*cursor == '\n') {
        ++cursor;
        --remaining_size;
        return terminal(terminal::type::new_line);
      }
    }
    return std::nullopt;
  }

  inline std::ostream& operator <<(std::ostream& out, const terminal& value) {
    if(value.get_type() == terminal::type::new_line) {
      return out << '\n';
    }
    return out;
  }

  inline bool operator ==(const terminal& lhs, const terminal& rhs) {
    return lhs.get_type() == rhs.get_type();
  }

  inline bool operator !=(const terminal& lhs, const terminal& rhs) {
    return !(lhs == rhs);
  }

  inline terminal::terminal(type type)
      : m_type(type) {}

  inline terminal::type terminal::get_type() const {
    return m_type;
  }
}

#endif

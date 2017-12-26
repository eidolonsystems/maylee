#ifndef MAYLEE_LOCATION_HPP
#define MAYLEE_LOCATION_HPP
#include <ostream>
#include <string>
#include <utility>
#include "maylee/lexicon/lexicon.hpp"
#include "maylee/lexicon/token.hpp"

namespace maylee {

  //! Represents a location in maylee source code.
  class location {
    public:

      //! Represents a location used for globally defined elements.
      static const location& global();

      //! Constructs a location.
      /*!
        \param path The path to the file containing the source code.
        \param line_number The source code's line number.
        \param column_number The source code's column number.
      */
      location(std::string path, int line_number, int column_number);

      //! Constructs a location representing a token.
      /*!
        \param path The path to the file containing the token.
        \param token The token whose location is to be represented.
      */
      location(std::string path, const token& token);

      //! Returns the path to the file containing the source code.
      const std::string& get_path() const;

      //! Returns the source code's line number.
      int get_line_number() const;

      //! Returns the source code's column number.
      int get_column_number() const;

    private:
      std::string m_path;
      int m_line_number;
      int m_column_number;
  };

  inline std::ostream& operator <<(std::ostream& out, const location& value) {
    return out << value.get_path() << ":" << value.get_line_number() << ":" <<
      value.get_column_number();
  }

  inline const location& location::global() {
    static location value("", 0, 0);
    return value;
  }

  inline location::location(std::string path, int line_number,
      int column_number)
      : m_path(std::move(path)),
        m_line_number(line_number),
        m_column_number(column_number) {}

  inline location::location(std::string path, const token& token)
      : location(std::move(path), token.get_line_number(),
          token.get_column_number()) {}

  inline const std::string& location::get_path() const {
    return m_path;
  }

  inline int location::get_line_number() const {
    return m_line_number;
  }

  inline int location::get_column_number() const {
    return m_column_number;
  }
}

#endif

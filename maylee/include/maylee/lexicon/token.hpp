#ifndef MAYLEE_TOKEN_HPP
#define MAYLEE_TOKEN_HPP
#include <ostream>
#include <utility>
#include "maylee/lexicon/identifier.hpp"
#include "maylee/lexicon/keyword.hpp"
#include "maylee/lexicon/literal.hpp"
#include "maylee/lexicon/lexicon.hpp"
#include "maylee/lexicon/punctuation.hpp"
#include "maylee/utilities/variant.hpp"

namespace maylee {

  //! Stores a single lexical token.
  class token {
    public:

      //! The types of tokens represented.
      enum class type {

        //! A keyword.
        KEYWORD,

        //! A punctuation mark.
        PUNCTUATION,

        //! A symbolic identifier.
        IDENTIFIER,

        //! A literal value.
        LITERAL,
      };

      //! A variant that stores the token's data.
      using instance = variant<keyword, punctuation, identifier, literal>;

      //! Constructs a keyword token.
      /*!
        \param instance The token's data.
        \param line_number The line number.
        \param column_number The column number.
      */
      token(instance instance, int line_number, int column_number);

      //! Returns the data associated with this token.
      const instance& get_instance() const;

      //! Returns the type of token.
      type get_type() const;

      //! Returns the line number.
      int get_line_number() const;

      //! Returns the column number.
      int get_column_number() const;

    private:
      instance m_instance;
      int m_line_number;
      int m_column_number;
  };

  inline std::ostream& operator <<(std::ostream& out, const token& value) {
    return out << value.get_instance();
  }

  inline token::token(instance instance, int line_number, int column_number)
      : m_instance(std::move(instance)),
        m_line_number(line_number),
        m_column_number(column_number) {}

  inline const token::instance& token::get_instance() const {
    return m_instance;
  }

  inline token::type token::get_type() const {
    return static_cast<type>(m_instance.get_which());
  }

  inline int token::get_line_number() const {
    return m_line_number;
  }

  inline int token::get_column_number() const {
    return m_column_number;
  }
}

#endif

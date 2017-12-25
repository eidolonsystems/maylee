#ifndef MAYLEE_TOKEN_HPP
#define MAYLEE_TOKEN_HPP
#include <ostream>
#include <utility>
#include <variant>
#include "maylee/lexicon/identifier.hpp"
#include "maylee/lexicon/keyword.hpp"
#include "maylee/lexicon/literal.hpp"
#include "maylee/lexicon/lexicon.hpp"
#include "maylee/lexicon/operation.hpp"
#include "maylee/lexicon/punctuation.hpp"
#include "maylee/lexicon/terminal.hpp"

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

        //! An operation.
        OPERATION,

        //! A symbolic identifier.
        IDENTIFIER,

        //! A literal value.
        LITERAL,

        //! The end of the module.
        TERMINAL
      };

      //! A variant that stores the token's data.
      using instance = std::variant<keyword, punctuation, operation, identifier,
        literal, terminal>;

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

  //! Tests if a token represents a particular instance.
  /*!
    \param t The token to test.
    \param i The instance to match.
    \return <code>true</code> iff the token matches the specified instance.
  */
  inline bool match(const token& t, const token::instance& i) {
    return t.get_instance() == i;
  }

  inline std::ostream& operator <<(std::ostream& out, const token& value) {
    return std::visit(
      [&] (auto& value) -> decltype(auto) {
        return out << value;
      },
      value.get_instance());
  }

  inline token::token(instance instance, int line_number, int column_number)
      : m_instance(std::move(instance)),
        m_line_number(line_number),
        m_column_number(column_number) {}

  inline const token::instance& token::get_instance() const {
    return m_instance;
  }

  inline token::type token::get_type() const {
    return static_cast<type>(m_instance.index());
  }

  inline int token::get_line_number() const {
    return m_line_number;
  }

  inline int token::get_column_number() const {
    return m_column_number;
  }
}

#endif

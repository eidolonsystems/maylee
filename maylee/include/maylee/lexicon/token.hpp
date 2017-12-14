#ifndef MAYLEE_TOKEN_HPP
#define MAYLEE_TOKEN_HPP
#include <ostream>
#include <utility>
#include "maylee/lexicon/identifier.hpp"
#include "maylee/lexicon/keyword.hpp"
#include "maylee/lexicon/lexicon.hpp"
#include "maylee/lexicon/punctuation.hpp"

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

        //! A terminal symbol (end-of-file).
        TERMINAL
      };

      //! Stores the data associated with this token.
      union instance {

        //! The keyword represented.
        keyword m_keyword;

        //! The punctuation represented.
        punctuation m_punctuation;

        //! The identifier represented.
        identifier m_identifier;

        instance() = delete;

        //! Constructs an instance from a keyword.
        /*!
          \param keyword The keyword to store.
        */
        instance(keyword keyword);

        //! Constructs an instance from a punctuation.
        /*!
          \param punctuation The punctuation to store.
        */
        instance(punctuation punctuation);

        //! Constructs an instance from an identifier.
        /*!
          \param identifier The identifier to store.
        */
        instance(identifier identifier);

        ~instance();
      };

      //! Constructs a keyword token.
      /*!
        \param keyword The keyword to represent.
        \param line_number The line number.
        \param column_number The column number.
      */
      token(keyword keyword, int line_number, int column_number);

      //! Constructs a punctuation token.
      /*!
        \param punctuation The punctuation to represent.
        \param line_number The line number.
        \param column_number The column number.
      */
      token(punctuation punctuation, int line_number, int column_number);

      //! Constructs an identifier token.
      /*!
        \param identifier The identifier to represent.
        \param line_number The line number.
        \param column_number The column number.
      */
      token(identifier identifier, int line_number, int column_number);

      ~token();

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
      type m_type;
      int m_line_number;
      int m_column_number;
  };

  inline std::ostream& operator <<(std::ostream& out, const token& value) {
    switch(value.get_type()) {
      case token::type::KEYWORD:
        return out << value.get_instance().m_keyword;
      case token::type::PUNCTUATION:
        return out << value.get_instance().m_punctuation;
      case token::type::IDENTIFIER:
        return out << value.get_instance().m_identifier;
      case token::type::TERMINAL:
        return out;
      default:
        throw std::invalid_argument("Invalid token.");
    }
  }

  inline token::instance::instance(keyword keyword)
      : m_keyword(std::move(keyword)) {}

  inline token::instance::instance(punctuation punctuation)
      : m_punctuation(std::move(punctuation)) {}

  inline token::instance::instance(identifier identifier)
      : m_identifier(std::move(identifier)) {}

  inline token::instance::~instance() {}

  inline token::token(keyword keyword, int line_number, int column_number)
      : m_instance(std::move(keyword)),
        m_type(type::KEYWORD),
        m_line_number(line_number),
        m_column_number(column_number) {}

  inline token::token(punctuation punctuation, int line_number,
      int column_number)
      : m_instance(std::move(punctuation)),
        m_type(type::PUNCTUATION),
        m_line_number(line_number),
        m_column_number(column_number) {}

  inline token::token(identifier identifier, int line_number, int column_number)
      : m_instance(std::move(identifier)),
        m_type(type::IDENTIFIER),
        m_line_number(line_number),
        m_column_number(column_number) {}

  inline token::~token() {
  }

  inline const token::instance& token::get_instance() const {
    return m_instance;
  }

  inline token::type token::get_type() const {
    return m_type;
  }

  inline int token::get_line_number() const {
    return m_line_number;
  }

  inline int token::get_column_number() const {
    return m_column_number;
  }
}

#endif

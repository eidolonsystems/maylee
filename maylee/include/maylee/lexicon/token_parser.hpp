#ifndef MAYLEE_TOKEN_PARSER_HPP
#define MAYLEE_TOKEN_PARSER_HPP
#include <memory>
#include <optional>
#include <vector>
#include "maylee/lexicon/lexicon.hpp"
#include "maylee/lexicon/token.hpp"

namespace maylee {

  //! Parses tokens from text.
  class token_parser {
    public:

      //! Constructs a token_parser.
      token_parser();

      //! Provides the parser with additional text.
      /*!
        \param data A pointer to the first character to feed.
        \param size The number of characters to feed.
      */
      void feed(const char* data, std::size_t size);

      //! Provides the parser with additional text.
      /*!
        \param data The text to feed to this parser.
      */
      template<std::size_t N>
      void feed(const char (&data)[N]);

      //! Parses the next token.
      /*!
        \return The token parsed from the previously fed text.
      */
      std::optional<token> parse_token();

    private:
      std::vector<char> m_data;
      int m_line_number;
      int m_column_number;
      const char* m_cursor;
      std::size_t m_remaining_size;

      token_parser(const token_parser&) = delete;
      token_parser& operator =(const token_parser&) = delete;
  };

  inline token_parser::token_parser()
      : m_line_number(0),
        m_column_number(0),
        m_cursor(m_data.data()),
        m_remaining_size(0) {}

  inline void token_parser::feed(const char* data, std::size_t size) {
    auto position = m_cursor - m_data.data();
    m_data.insert(m_data.end(), data, data + size);
    m_cursor = m_data.data() + position;
    m_remaining_size += size;
  }

  template<std::size_t N>
  void token_parser::feed(const char (&data)[N]) {
    feed(data, N - 1);
  }

  inline std::optional<token> token_parser::parse_token() {
    while(m_remaining_size != 0) {
      if(std::isspace(*m_cursor)) {
        if(*m_cursor == '\n') {
          ++m_line_number;
          m_column_number = 0;
        } else {
          ++m_column_number;
        }
        ++m_cursor;
        --m_remaining_size;
      } else {
        break;
      }
    }
    auto remaining_size = m_remaining_size;
    if(auto keyword = parse_keyword(m_cursor, remaining_size)) {
      auto column_number = m_column_number;
      m_column_number += (m_remaining_size - remaining_size);
      m_remaining_size = remaining_size;
      return std::make_optional<token>(
        {std::move(*keyword), m_line_number, column_number});
    } else if(auto punctuation = parse_punctuation(m_cursor, remaining_size)) {
      auto column_number = m_column_number;
      m_column_number += (m_remaining_size - remaining_size);
      m_remaining_size = remaining_size;
      return std::make_optional<token>(
        {std::move(*punctuation), m_line_number, column_number});
    } else if(auto operation = parse_operation(m_cursor, remaining_size)) {
      auto column_number = m_column_number;
      m_column_number += (m_remaining_size - remaining_size);
      m_remaining_size = remaining_size;
      return std::make_optional<token>(
        {std::move(*operation), m_line_number, column_number});
    } else if(auto literal = parse_literal(m_cursor, remaining_size)) {
      auto column_number = m_column_number;
      m_column_number += (m_remaining_size - remaining_size);
      m_remaining_size = remaining_size;
      return std::make_optional<token>(
        {std::move(*literal), m_line_number, column_number});
    } else if(auto identifier = parse_identifier(m_cursor, remaining_size)) {
      auto column_number = m_column_number;
      m_column_number += (m_remaining_size - remaining_size);
      m_remaining_size = remaining_size;
      return std::make_optional<token>(
        {std::move(*identifier), m_line_number, column_number});
    } else if(auto terminal = parse_terminal(m_cursor, remaining_size)) {
      auto line_number = m_line_number;
      auto column_number = m_column_number;
      m_line_number = 0;
      m_column_number = 0;
      return std::make_optional<token>(
        {std::move(*terminal), line_number, column_number});
    }
    return std::nullopt;
  }
}

#endif

#ifndef MAYLEE_TOKEN_PARSER_HPP
#define MAYLEE_TOKEN_PARSER_HPP
#include <array>
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
      bool m_parsed_new_line;
      bool m_parsed_line_continuation;
      std::array<int, 2> m_bracket_count;

      token_parser(const token_parser&) = delete;
      token_parser& operator =(const token_parser&) = delete;
      void update_bracket_count(const punctuation& p);
      bool is_new_line_signifcant() const;
  };

  inline token_parser::token_parser()
      : m_line_number(0),
        m_column_number(0),
        m_cursor(m_data.data()),
        m_remaining_size(0),
        m_parsed_new_line(true),
        m_parsed_line_continuation(false) {
    m_bracket_count.fill(0);
  }

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
          if(is_new_line_signifcant()) {
            ++m_cursor;
            --m_remaining_size;
            auto line_number = m_line_number;
            auto column_number = m_column_number;
            ++m_line_number;
            m_column_number = 0;
            m_parsed_new_line = true;
            return std::make_optional<token>(
              {terminal::type::new_line, line_number, column_number});
          }
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
    if(m_remaining_size == 0) {
      return std::nullopt;
    }
    auto parsed_line_continuation = m_parsed_line_continuation;
    m_parsed_line_continuation = false;
    m_parsed_new_line = false;
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
      update_bracket_count(*punctuation);
      return std::make_optional<token>(
        {std::move(*punctuation), m_line_number, column_number});
    } else if(auto operation = parse_operation(m_cursor, remaining_size)) {
      auto column_number = m_column_number;
      m_column_number += (m_remaining_size - remaining_size);
      m_remaining_size = remaining_size;
      m_parsed_line_continuation = true;
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
    m_parsed_line_continuation = parsed_line_continuation;
    return std::nullopt;
  }

  inline void token_parser::update_bracket_count(const punctuation& p) {
    switch(p.get_mark()) {
      case punctuation::mark::OPEN_BRACKET:
        ++m_bracket_count[0];
        return;
      case punctuation::mark::CLOSE_BRACKET:
        --m_bracket_count[0];
        return;
    }
  }

  inline bool token_parser::is_new_line_signifcant() const {
    if(m_parsed_line_continuation || m_parsed_new_line) {
      return false;
    }
    for(auto& count : m_bracket_count) {
      if(count != 0) {
        return false;
      }
    }
    return true;
  }
}

#endif

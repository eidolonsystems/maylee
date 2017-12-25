#ifndef MAYLEE_SYNTAX_PARSER_HPP
#define MAYLEE_SYNTAX_PARSER_HPP
#include <memory>
#include <string>
#include <type_traits>
#include <vector>
#include "maylee/lexicon/token.hpp"
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/syntax_error_code.hpp"
#include "maylee/syntax/syntax_error.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node.hpp"
#include "maylee/syntax/terminal_node.hpp"

namespace maylee {

  //! Parses syntax nodes from tokens.
  class syntax_parser {
    public:

      //! Constructs a default syntax parser.
      syntax_parser();

      //! Feeds this parser a token.
      /*!
        \param t The token to feed.
      */
      void feed(token t);

      //! Parses the next syntax node.
      /*!
        \return The syntax node parsed from the previously fed tokens or
                <code>nullptr</code> iff no syntax node is available.
      */
      std::unique_ptr<syntax_node> parse_node();

    private:
      std::vector<token> m_tokens;
      std::vector<token>::iterator m_cursor;
      std::size_t m_remaining_size;

      syntax_parser(const syntax_parser&) = delete;
      syntax_parser& operator =(const syntax_parser&) = delete;
      std::unique_ptr<terminal_node> parse_terminal_node(
        std::vector<token>::iterator& cursor, std::size_t& size);
      std::unique_ptr<let_expression> parse_let_expression(
        std::vector<token>::iterator& cursor, std::size_t& size);
      std::unique_ptr<literal_expression> parse_literal_expression(
        std::vector<token>::iterator& cursor, std::size_t& size);
      std::unique_ptr<expression> parse_expression(
        std::vector<token>::iterator& cursor, std::size_t& size);
  };

  //! Parses an identifier from a token stream.
  /*!
    \param cursor An iterator to the first token to parse.
    \param size The number of tokens remaining.
    \return The symbol represented by the parsed identifier.
  */
  template<typename I>
  const std::string& parse_identifier(I& cursor, std::size_t& size) {
    if(size == 0) {
      throw syntax_error(syntax_error_code::IDENTIFIER_EXPECTED, *cursor);
    }
    return std::visit(
      [&] (auto&& value) -> const std::string& {
        using T = std::decay_t<decltype(value)>;
        if constexpr(std::is_same_v<T, identifier>) {
          ++cursor;
          --size;
          return value.get_symbol();
        }
        throw syntax_error(syntax_error_code::IDENTIFIER_EXPECTED, *cursor);
      },
      cursor->get_instance());
  }

  //! Ensures that a token represents an assignment operation.
  /*!
    \param cursor An iterator to the first token to parse.
    \param size The number of tokens remaining.
  */
  template<typename I>
  void require_assignment(I& cursor, std::size_t& size) {
    if(size == 0) {
      throw syntax_error(syntax_error_code::ASSIGNMENT_EXPECTED, *cursor);
    }
    std::visit(
      [&] (auto&& value) {
        using T = std::decay_t<decltype(value)>;
        if constexpr(std::is_same_v<T, operation>) {
          if(value.get_symbol() == operation::symbol::ASSIGN) {
            ++cursor;
            --size;
            return;
          }
        }
        throw syntax_error(syntax_error_code::ASSIGNMENT_EXPECTED, *cursor);
      },
      cursor->get_instance());
  }

  inline syntax_parser::syntax_parser()
      : m_cursor(m_tokens.begin()),
        m_remaining_size(0) {}

  inline void syntax_parser::feed(token t) {
    auto position = m_cursor - m_tokens.begin();
    m_tokens.push_back(std::move(t));
    m_cursor = m_tokens.begin() + position;
    ++m_remaining_size;
  }

  inline std::unique_ptr<syntax_node> syntax_parser::parse_node() {
    if(m_remaining_size == 0) {
      return nullptr;
    }
    if(auto node = parse_expression(m_cursor, m_remaining_size)) {
      return node;
    }
    if(auto node = parse_terminal_node(m_cursor, m_remaining_size)) {
      return node;
    }
    return nullptr;
  }

  inline std::unique_ptr<terminal_node> syntax_parser::parse_terminal_node(
      std::vector<token>::iterator& cursor, std::size_t& size) {
    if(size != 0 && match(*cursor, terminal())) {
      ++cursor;
      --size;
      return std::make_unique<terminal_node>();
    }
    return nullptr;
  }
}

#include "syntax_parser_expressions.hpp"
#endif

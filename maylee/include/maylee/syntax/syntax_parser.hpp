#ifndef MAYLEE_SYNTAX_PARSER_HPP
#define MAYLEE_SYNTAX_PARSER_HPP
#include <deque>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>
#include "maylee/lexicon/token.hpp"
#include "maylee/syntax/expression.hpp"
#include "maylee/syntax/scope.hpp"
#include "maylee/syntax/syntax_error_code.hpp"
#include "maylee/syntax/syntax_error.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node.hpp"
#include "maylee/syntax/terminal_node.hpp"
#include "maylee/syntax/token_iterator.hpp"

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
      token_iterator m_cursor;
      std::deque<std::unique_ptr<scope>> m_scopes;
      int m_new_lines;

      syntax_parser(const syntax_parser&) = delete;
      syntax_parser& operator =(const syntax_parser&) = delete;
      scope& get_scope();
      scope& push_scope();
      scope& pop_scope();
      std::unique_ptr<terminal_node> parse_terminal_node(
        token_iterator& cursor);
      std::unique_ptr<if_expression> parse_if_expression(
        token_iterator& cursor);
      std::unique_ptr<let_expression> parse_let_expression(
        token_iterator& cursor);
      std::unique_ptr<literal_expression> parse_literal_expression(
        token_iterator& cursor);
      std::unique_ptr<variable_expression> parse_variable_expression(
        token_iterator& cursor);
      std::unique_ptr<expression> parse_expression_term(token_iterator& cursor);
      std::unique_ptr<expression> parse_expression(token_iterator& cursor);
  };

  //! Parses an identifier from a token stream.
  /*!
    \param cursor An iterator to the first token to parse.
    \return The symbol represented by the parsed identifier.
  */
  inline const std::string& parse_identifier(token_iterator& cursor) {
    if(cursor.is_empty()) {
      throw syntax_error(syntax_error_code::IDENTIFIER_EXPECTED,
        cursor.get_location());
    }
    return std::visit(
      [&] (auto&& value) -> const std::string& {
        using T = std::decay_t<decltype(value)>;
        if constexpr(std::is_same_v<T, identifier>) {
          ++cursor;
          return value.get_symbol();
        }
        throw syntax_error(syntax_error_code::IDENTIFIER_EXPECTED,
          cursor.get_location());
      },
      cursor->get_instance());
  }

  //! Parses an identifier from a token stream.
  /*!
    \param cursor An iterator to the first token to parse.
    \return The symbol represented by the parsed identifier.
  */
  inline std::optional<std::string> try_parse_identifier(
      token_iterator& cursor) {
    try {
      return parse_identifier(cursor);
    } catch(const syntax_error&) {
      return std::nullopt;
    }
  }

  //! Ensures that a token represents an assignment operation.
  /*!
    \param cursor An iterator to the first token to parse.
    \param size The number of tokens remaining.
  */
  inline void require_assignment(token_iterator& cursor) {
    if(cursor.is_empty()) {
      throw syntax_error(syntax_error_code::ASSIGNMENT_EXPECTED,
        cursor.get_location());
    }
    std::visit(
      [&] (auto&& value) {
        using T = std::decay_t<decltype(value)>;
        if constexpr(std::is_same_v<T, operation>) {
          if(value.get_symbol() == operation::symbol::ASSIGN) {
            ++cursor;
            return;
          }
        }
        throw syntax_error(syntax_error_code::ASSIGNMENT_EXPECTED,
          cursor.get_location());
      },
      cursor->get_instance());
  }

  inline syntax_parser::syntax_parser()
      : m_new_lines(0) {
    m_scopes.push_back(std::make_unique<scope>());
    populate_global_scope(*m_scopes.back());
  }

  inline void syntax_parser::feed(token t) {
    if(is_terminal(t)) {
      ++m_new_lines;
    }
    auto position = &*m_cursor - m_tokens.data();
    m_tokens.push_back(std::move(t));
    m_cursor.adjust(m_tokens.data() + position,
      m_cursor.get_size_remaining() + 1);
  }

  inline std::unique_ptr<syntax_node> syntax_parser::parse_node() {
    if(m_new_lines == 0) {
      return nullptr;
    }
    std::unique_ptr<syntax_node> node;
    if(((node = parse_expression(m_cursor)) != nullptr) ||
        ((node = parse_terminal_node(m_cursor)) != nullptr)) {
      if(is_terminal(*m_cursor)) {
        --m_new_lines;
        ++m_cursor;
        return node;
      }
      throw syntax_error(syntax_error_code::NEW_LINE_EXPECTED,
        m_cursor.get_location());
    }
    return nullptr;
  }

  inline scope& syntax_parser::get_scope() {
    return *m_scopes.back();
  }

  inline scope& syntax_parser::push_scope() {
    m_scopes.push_back(std::make_unique<scope>(&get_scope()));
    return get_scope();
  }

  inline scope& syntax_parser::pop_scope() {
    m_scopes.pop_back();
    return get_scope();
  }

  inline std::unique_ptr<terminal_node> syntax_parser::parse_terminal_node(
      token_iterator& cursor) {
    if(!cursor.is_empty() && match(*cursor, terminal::type::end_of_file)) {
      return std::make_unique<terminal_node>();
    }
    return nullptr;
  }
}

#include "syntax_parser_expressions.hpp"
#endif

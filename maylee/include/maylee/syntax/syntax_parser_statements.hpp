#ifndef MAYLEE_SYNTAX_PARSER_STATEMENTS_HPP
#define MAYLEE_SYNTAX_PARSER_STATEMENT_HPP
#include <cassert>
#include "maylee/lexicon/token.hpp"
#include "maylee/syntax/block_statement.hpp"
#include "maylee/syntax/if_statement.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_error.hpp"
#include "maylee/syntax/syntax_parser.hpp"

namespace maylee {
  inline std::unique_ptr<if_statement> syntax_parser::parse_if_statement(
      token_iterator& cursor) {
    struct clause {
      std::unique_ptr<expression> m_condition;
      std::unique_ptr<statement> m_consequence;
    };
    auto c = cursor;
    if(!match(*c, keyword::word::IF)) {
      return nullptr;
    }
    std::vector<clause> clauses;
    while(true) {
      ++c;
      auto condition = parse_expression(c);
      if(condition == nullptr) {
        throw syntax_error(syntax_error_code::EXPRESSION_EXPECTED,
          c.get_location());
      }
      expect(c, punctuation::mark::COLON);
      push_scope();
      std::vector<std::unique_ptr<statement>> consequents;
      while(!match(*c, keyword::word::END) && !match(*c, keyword::word::ELSE) &&
          !match(*c, keyword::word::ELSE_IF)) {
        consequents.push_back(parse_statement(c));
      }
      auto s = pop_scope();
      auto consequent = std::make_unique<block_statement>(std::move(s),
        std::move(consequents));
      clauses.push_back({std::move(condition), std::move(consequent)});
      if(!match(*c, keyword::word::ELSE_IF)) {
        break;
      }
    }
    auto alternative =
      [&] () -> std::unique_ptr<statement> {
        if(match(*c, keyword::word::ELSE)) {
          if(c.is_empty()) {
            return nullptr;
          }
          ++c;
          expect(c, punctuation::mark::COLON);
          push_scope();
          std::vector<std::unique_ptr<statement>> consequents;
          while(!match(*c, keyword::word::END)) {
            consequents.push_back(parse_statement(c));
          }
          auto s = pop_scope();
          return std::make_unique<block_statement>(std::move(s),
            std::move(consequents));
        } else {
          return std::make_unique<void_expression>();
        }
      }();
    if(alternative == nullptr) {
      return nullptr;
    }
    auto end_clause = std::move(clauses.back());
    clauses.pop_back();
    auto bottom = std::make_unique<if_statement>(
      std::move(end_clause.m_condition), std::move(end_clause.m_consequence),
      std::move(alternative));
    while(!clauses.empty()) {
      auto end_clause = std::move(clauses.back());
      clauses.pop_back();
      bottom = std::make_unique<if_statement>(std::move(end_clause.m_condition),
        std::move(end_clause.m_consequence), std::move(bottom));
    }
    cursor = c;
    return bottom;
  }

  inline std::unique_ptr<terminal_node> syntax_parser::parse_terminal_node(
      token_iterator& cursor) {
    if(!cursor.is_empty() && match(*cursor, terminal::type::end_of_file)) {
      ++cursor;
      return std::make_unique<terminal_node>();
    }
    return nullptr;
  }

  inline std::unique_ptr<statement> syntax_parser::parse_statement(
      token_iterator& cursor) {
    if(auto node = parse_expression(cursor)) {
      return node;
    } else if(auto node = parse_if_statement(cursor)) {
      return node;
    }
    return nullptr;
  }
}

#endif

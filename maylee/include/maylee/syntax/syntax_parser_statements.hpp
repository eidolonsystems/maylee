#ifndef MAYLEE_SYNTAX_PARSER_STATEMENTS_HPP
#define MAYLEE_SYNTAX_PARSER_STATEMENT_HPP
#include <cassert>
#include "maylee/lexicon/token.hpp"
#include "maylee/syntax/block_statement.hpp"
#include "maylee/syntax/function_definition.hpp"
#include "maylee/syntax/if_statement.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_error.hpp"
#include "maylee/syntax/syntax_parser.hpp"

namespace maylee {
  inline std::unique_ptr<function_definition>
      syntax_parser::parse_function_definition(token_iterator& cursor) {
    auto c = cursor;
    if(!match(*c, keyword::word::DEFINE)) {
      return nullptr;
    }
    ++c;
    if(c.is_empty()) {
      return nullptr;
    }
    auto identifier_cursor = c;
    auto& name = parse_identifier(c);
    if(c.is_empty()) {
      return nullptr;
    }
    expect(c, bracket::type::OPEN_ROUND_BRACKET);
    std::vector<function_definition::parameter> parameters;
    while(!match(*c, bracket::type::CLOSE_ROUND_BRACKET)) {
      auto identifier_cursor = c;
      auto& name = parse_identifier(c);
      if(std::find_if(parameters.begin(), parameters.end(),
          [&] (auto& parameter) {
            return parameter.m_name == name;
          }) != parameters.end()) {
      // TODO
//      throw redefinition_syntax_error(identifier_cursor.get_location(), name,
//        existing_element->get_location());
      }
      expect(c, punctuation::mark::COLON);
      auto type = parse_expression(c);
      parameters.push_back({name, std::move(type)});
    }
    ++c;
    if(c.is_empty()) {
      return nullptr;
    }
    expect(c, punctuation::mark::COLON);
    std::vector<std::unique_ptr<statement>> body;
    while(!match(*c, keyword::word::END)) {
      body.push_back(parse_statement(c));
    }
    ++c;
    cursor = c;
    return std::make_unique<function_definition>(name, std::move(parameters),
      std::make_unique<block_statement>(std::move(body)));
  }

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
      std::vector<std::unique_ptr<statement>> consequents;
      while(!match(*c, keyword::word::END) && !match(*c, keyword::word::ELSE) &&
          !match(*c, keyword::word::ELSE_IF)) {
        consequents.push_back(parse_statement(c));
      }
      auto consequent = std::make_unique<block_statement>(
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
          std::vector<std::unique_ptr<statement>> consequents;
          while(!match(*c, keyword::word::END)) {
            consequents.push_back(parse_statement(c));
          }
          return std::make_unique<block_statement>(std::move(consequents));
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
    auto c = cursor;
    std::unique_ptr<statement> node;
    if((node = parse_if_statement(c)) != nullptr ||
        (node = parse_function_definition(c)) != nullptr ||
        (node = parse_expression(c)) != nullptr) {
      if(!is_syntax_node_end(*c)) {
        throw syntax_error(syntax_error_code::NEW_LINE_EXPECTED,
          c.get_location());
      }
      cursor = c;
      return node;
    }
    return nullptr;
  }
}

#endif

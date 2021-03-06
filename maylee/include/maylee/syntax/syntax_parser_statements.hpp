#ifndef MAYLEE_SYNTAX_PARSER_STATEMENTS_HPP
#define MAYLEE_SYNTAX_PARSER_STATEMENT_HPP
#include <cassert>
#include "maylee/lexicon/token.hpp"
#include "maylee/syntax/assignment_statement.hpp"
#include "maylee/syntax/block_statement.hpp"
#include "maylee/syntax/function_definition.hpp"
#include "maylee/syntax/if_statement.hpp"
#include "maylee/syntax/function_parameter_redefinition_syntax_error.hpp"
#include "maylee/syntax/return_statement.hpp"
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
    auto& name = parse_identifier(c);
    expect(c, bracket::type::OPEN_ROUND_BRACKET);
    std::vector<function_definition::parameter> parameters;
    std::vector<location> parameter_locations;
    while(!match(*c, bracket::type::CLOSE_ROUND_BRACKET)) {
      auto identifier_cursor = c;
      auto& name = parse_identifier(c);
      auto existing_parameter = std::find_if(parameters.begin(),
        parameters.end(),
        [&] (auto& parameter) {
          return parameter.m_name == name;
        });
      if(existing_parameter != parameters.end()) {
        auto existing_index = std::distance(existing_parameter,
          parameters.begin());
        throw function_parameter_redefinition_syntax_error(
          identifier_cursor.get_location(), name,
          parameter_locations[existing_index]);
      }
      expect(c, punctuation::mark::COLON);
      auto type = expect_expression(c);
      parameters.push_back({name, std::move(type)});
      parameter_locations.push_back(identifier_cursor.get_location());
    }
    ++c;
    auto block_location = c.get_location();
    expect(c, punctuation::mark::COLON);
    while(match(*c, terminal::type::new_line)) {
      ++c;
    }
    std::vector<std::unique_ptr<statement>> body;
    while(!match(*c, keyword::word::END)) {
      body.push_back(expect_statement(c));
    }
    ++c;
    auto f = std::make_unique<function_definition>(cursor.get_location(), name,
      std::move(parameters),
      std::make_unique<block_statement>(block_location, std::move(body)));
    cursor = c;
    return f;
  }

  inline std::unique_ptr<if_statement> syntax_parser::parse_if_statement(
      token_iterator& cursor) {
    struct clause {
      location m_location;
      std::unique_ptr<expression> m_condition;
      std::unique_ptr<statement> m_consequence;
    };
    auto c = cursor;
    if(!match(*c, keyword::word::IF)) {
      return nullptr;
    }
    std::vector<clause> clauses;
    while(true) {
      auto clause_location = c.get_location();
      ++c;
      auto condition = expect_expression(c);
      auto block_location = c.get_location();
      expect(c, punctuation::mark::COLON);
      while(match(*c, terminal::type::new_line)) {
        ++c;
      }
      std::vector<std::unique_ptr<statement>> consequents;
      while(!match(*c, keyword::word::END) && !match(*c, keyword::word::ELSE) &&
          !match(*c, keyword::word::ELSE_IF)) {
        consequents.push_back(expect_statement(c));
      }
      auto consequent = std::make_unique<block_statement>(block_location,
        std::move(consequents));
      clauses.push_back({std::move(clause_location), std::move(condition),
        std::move(consequent)});
      if(!match(*c, keyword::word::ELSE_IF)) {
        break;
      }
    }
    auto alternative =
      [&] () -> std::unique_ptr<statement> {
        if(match(*c, keyword::word::ELSE)) {
          ++c;
          auto block_location = c.get_location();
          expect(c, punctuation::mark::COLON);
          while(match(*c, terminal::type::new_line)) {
            ++c;
          }
          std::vector<std::unique_ptr<statement>> consequents;
          while(!match(*c, keyword::word::END)) {
            consequents.push_back(expect_statement(c));
          }
          return std::make_unique<block_statement>(block_location,
            std::move(consequents));
        } else {
          return std::make_unique<void_expression>(c.get_location());
        }
      }();
    auto end_clause = std::move(clauses.back());
    clauses.pop_back();
    auto bottom = std::make_unique<if_statement>(
      std::move(end_clause.m_location), std::move(end_clause.m_condition),
      std::move(end_clause.m_consequence), std::move(alternative));
    while(!clauses.empty()) {
      auto end_clause = std::move(clauses.back());
      clauses.pop_back();
      bottom = std::make_unique<if_statement>(std::move(end_clause.m_location),
        std::move(end_clause.m_condition), std::move(end_clause.m_consequence),
        std::move(bottom));
    }
    cursor = c;
    return bottom;
  }

  inline std::unique_ptr<return_statement>
      syntax_parser::parse_return_statement(token_iterator& cursor) {
    auto c = cursor;
    if(!match(*c, keyword::word::RETURN)) {
      return nullptr;
    }
    ++c;
    if(is_syntax_node_end(*c)) {
      auto r = std::make_unique<return_statement>(cursor.get_location());
      cursor = c;
      return r;
    }
    auto result = expect_expression(c);
    auto r = std::make_unique<return_statement>(cursor.get_location(),
      std::move(result));
    cursor = c;
    return r;
  }

  inline std::unique_ptr<terminal_node> syntax_parser::parse_terminal_node(
      token_iterator& cursor) {
    if(!cursor.is_empty() && match(*cursor, terminal::type::end_of_file)) {
      auto t = std::make_unique<terminal_node>(cursor.get_location());
      ++cursor;
      return t;
    }
    return nullptr;
  }

  inline std::unique_ptr<statement> syntax_parser::parse_statement(
      token_iterator& cursor) {
    auto c = cursor;
    while(!c.is_empty() && match(*c, terminal::type::new_line)) {
      ++c;
    }
    std::unique_ptr<statement> node;
    if((node = parse_if_statement(c)) != nullptr ||
        (node = parse_function_definition(c)) != nullptr ||
        (node = parse_return_statement(c)) != nullptr) {
      if(!is_syntax_node_end(*c)) {
        throw syntax_error(syntax_error_code::NEW_LINE_EXPECTED,
          c.get_location());
      }
      while(!c.is_empty() && match(*c, terminal::type::new_line)) {
        ++c;
      }
      cursor = c;
      return node;
    } else if(auto expression = parse_expression(c)) {
      if(c.is_empty()) {
        return nullptr;
      } else if(match(*c, operation::symbol::ASSIGN)) {
        auto assign_location = c.get_location();
        ++c;
        auto value = parse_expression(c);
        if(value == nullptr) {
          throw syntax_error(syntax_error_code::EXPRESSION_EXPECTED,
            c.get_location());
        }
        node = std::make_unique<assignment_statement>(assign_location,
          std::move(expression), std::move(value));
      } else {
        node = std::move(expression);
      }
      if(!is_syntax_node_end(*c)) {
        throw syntax_error(syntax_error_code::NEW_LINE_EXPECTED,
          c.get_location());
      }
      while(!c.is_empty() && match(*c, terminal::type::new_line)) {
        ++c;
      }
      cursor = c;
      return node;
    }
    return nullptr;
  }

  inline std::unique_ptr<statement> syntax_parser::expect_statement(
      token_iterator& cursor) {
    auto s = parse_statement(cursor);
    if(s == nullptr) {
      throw syntax_error(syntax_error_code::STATEMENT_EXPECTED,
        cursor.get_location());
    }
    return s;
  }
}

#endif

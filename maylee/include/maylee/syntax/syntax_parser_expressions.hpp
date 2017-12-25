#ifndef MAYLEE_SYNTAX_PARSER_EXPRESSIONS_HPP
#define MAYLEE_SYNTAX_PARSER_EXPRESSIONS_HPP
#include "maylee/lexicon/token.hpp"
#include "maylee/syntax/let_expression.hpp"
#include "maylee/syntax/literal_expression.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_parser.hpp"

namespace maylee {
  inline std::unique_ptr<let_expression> syntax_parser::parse_let_expression(
      std::vector<token>::iterator& cursor, std::size_t& size) {
    if(size == 0) {
      return nullptr;
    }
    auto c = cursor;
    auto s = size;
    if(!match(*c, keyword::word::LET)) {
      return nullptr;
    }
    ++c;
    --s;
    if(s == 0) {
      return nullptr;
    }
    auto& name = parse_identifier(c, s);
    if(s == 0) {
      return nullptr;
    }
    require_assignment(c, s);
    auto initializer = parse_expression(c, s);
    if(initializer == nullptr) {
      return nullptr;
    }
    return std::make_unique<let_expression>(name,
      initializer->get_evaluation_type(), std::move(initializer));
  }

  inline std::unique_ptr<literal_expression> syntax_parser::
      parse_literal_expression(std::vector<token>::iterator& cursor,
      std::size_t& size) {
    if(size == 0) {
      return nullptr;
    }
    return std::visit(
      [&] (auto&& value) -> std::unique_ptr<literal_expression> {
        using T = std::decay_t<decltype(value)>;
        if constexpr(std::is_same_v<T, literal>) {
          auto expression = std::make_unique<literal_expression>(value);
          ++cursor;
          --size;
          return expression;
        }
        return nullptr;
      },
      cursor->get_instance());
  }

  inline std::unique_ptr<expression> syntax_parser::parse_expression(
      std::vector<token>::iterator& cursor, std::size_t& size) {
    if(size == 0) {
      return nullptr;
    }
    if(auto node = parse_literal_expression(cursor, size)) {
      return node;
    } else if(auto node = parse_let_expression(cursor, size)) {
      return node;
    }
    return nullptr;
  }
}

#endif

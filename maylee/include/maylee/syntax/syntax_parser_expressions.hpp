#ifndef MAYLEE_SYNTAX_PARSER_EXPRESSIONS_HPP
#define MAYLEE_SYNTAX_PARSER_EXPRESSIONS_HPP
#include <deque>
#include <stack>
#include "maylee/lexicon/token.hpp"
#include "maylee/syntax/call_expression.hpp"
#include "maylee/syntax/let_expression.hpp"
#include "maylee/syntax/literal_expression.hpp"
#include "maylee/syntax/ops.hpp"
#include "maylee/syntax/redefinition_syntax_error.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_error.hpp"
#include "maylee/syntax/syntax_parser.hpp"
#include "maylee/syntax/variable_expression.hpp"

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
    auto identifier_token = *c;
    auto& name = parse_identifier(get_current_module(), c, s);
    auto existing_element = get_scope().find_within(name);
    if(existing_element.has_value()) {
      throw redefinition_syntax_error(
        location(get_current_module(), identifier_token), name,
        existing_element->get_location());
    }
    if(s == 0) {
      return nullptr;
    }
    require_assignment(get_current_module(), c, s);
    auto initializer = parse_expression(c, s);
    if(initializer == nullptr) {
      return nullptr;
    }
    auto expression = std::make_unique<let_expression>(name,
      initializer->get_evaluation_type(), std::move(initializer));
    m_scopes.back()->add(element(std::make_shared<variable>(
      name, expression->get_evaluation_type()),
      location("", identifier_token)));
    cursor = c;
    size = s;
    return expression;
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

  inline std::unique_ptr<variable_expression>
      syntax_parser::parse_variable_expression(
      std::vector<token>::iterator& cursor, std::size_t& size) {
    auto c = cursor;
    auto s = size;
    auto name = try_parse_identifier(get_current_module(), c, s);
    if(!name.has_value()) {
      return nullptr;
    }
    auto element = get_scope().find(*name);
    if(!element.has_value()) {
      return nullptr;
    }
    if(auto v = std::get_if<std::shared_ptr<variable>>(
        &element->get_instance())) {
      cursor = c;
      size = s;
      return std::make_unique<variable_expression>(*v);
    }
    return nullptr;
  }

  inline std::unique_ptr<expression> syntax_parser::parse_expression_term(
      std::vector<token>::iterator& cursor, std::size_t& size) {
    if(auto node = parse_literal_expression(cursor, size)) {
      return node;
    } else if(auto node = parse_let_expression(cursor, size)) {
      return node;
    } else if(auto node = parse_variable_expression(cursor, size)) {
      return node;
    }
    return nullptr;
  }

  inline std::unique_ptr<expression> syntax_parser::parse_expression(
      std::vector<token>::iterator& cursor, std::size_t& size) {
    std::deque<std::unique_ptr<expression>> expressions;
    std::stack<op> operators;
    auto build_call_expression =
      [&] (op o) {
        auto arity = get_arity(o);
        if(static_cast<int>(expressions.size()) < arity) {
          // TODO: Throw exception.
        }
        std::vector<std::unique_ptr<expression>> parameters;
        for(auto i = 0; i < arity; ++i) {
          parameters.push_back(nullptr);
        }
        while(arity != 0) {
          parameters[arity - 1] = std::move(expressions.back());
          expressions.pop_back();
          --arity;
        }

        // TODO: Resolve missing return type.
        auto call = std::make_unique<call_expression>(nullptr,
          std::move(parameters), bool_data_type::get_instance());
        expressions.push_back(std::move(call));
      };
    auto c = cursor;
    auto s = size;
    while(s != 0) {
      if(c->get_type() == token::type::OPERATION) {
        auto o = get_op(std::get<operation>(c->get_instance()));
        while(!operators.empty() &&
            (operators.top() != op::OPEN_BRACKET &&
            operators.top() != op::CLOSE_BRACKET &&
            (get_precedence(operators.top()) > get_precedence(o) ||
            get_precedence(operators.top()) == get_precedence(o) &&
            get_associativity(o) == associativity::LEFT_TO_RIGHT))) {
          build_call_expression(operators.top());
          operators.pop();
        }
        operators.push(o);
        ++c;
        --s;
      } else if(match(*c, punctuation::mark::OPEN_BRACKET)) {
        ++c;
        --s;
        operators.push(op::OPEN_BRACKET);
      } else if(match(*c, punctuation::mark::CLOSE_BRACKET)) {
        auto found_open_bracket = false;
        while(!operators.empty()) {
          auto o = operators.top();
          operators.pop();
          if(o == op::OPEN_BRACKET) {
            found_open_bracket = true;
            break;
          } else {
            build_call_expression(o);
          }
        }
        if(!found_open_bracket) {
          // TODO: Throw exception.
        }
      } else if(auto node = parse_expression_term(c, s)) {
        expressions.push_back(std::move(node));
      } else {
        break;
      }
    }
    while(!operators.empty()) {
      auto o = operators.top();
      operators.pop();
      if(o == op::OPEN_BRACKET || o == op::CLOSE_BRACKET) {
        // TODO: Throw exception.
      }
      build_call_expression(o);
    }
    if(expressions.empty()) {
      return nullptr;
    } else if(expressions.size() != 1) {
      // TODO: Throw exception.
    }
    auto e = std::move(expressions.front());
    expressions.pop_front();
    return e;
  }
}

#endif

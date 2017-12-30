#ifndef MAYLEE_SYNTAX_PARSER_EXPRESSIONS_HPP
#define MAYLEE_SYNTAX_PARSER_EXPRESSIONS_HPP
#include <cassert>
#include <deque>
#include <stack>
#include "maylee/lexicon/token.hpp"
#include "maylee/syntax/arity_syntax_error.hpp"
#include "maylee/syntax/call_expression.hpp"
#include "maylee/syntax/if_expression.hpp"
#include "maylee/syntax/let_expression.hpp"
#include "maylee/syntax/literal_expression.hpp"
#include "maylee/syntax/ops.hpp"
#include "maylee/syntax/redefinition_syntax_error.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_error.hpp"
#include "maylee/syntax/syntax_parser.hpp"
#include "maylee/syntax/unmatched_bracket_syntax_error.hpp"
#include "maylee/syntax/variable_expression.hpp"

namespace maylee {
  inline std::unique_ptr<if_expression>
      syntax_parser::parse_if_expression(token_iterator& cursor) {
    return nullptr;
  }

  inline std::unique_ptr<let_expression> syntax_parser::parse_let_expression(
      token_iterator& cursor) {
    if(cursor.is_empty()) {
      return nullptr;
    }
    auto c = cursor;
    if(!match(*c, keyword::word::LET)) {
      return nullptr;
    }
    ++c;
    if(c.is_empty()) {
      return nullptr;
    }
    auto identifier_cursor = c;
    auto& name = parse_identifier(c);
    auto existing_element = get_scope().find_within(name);
    if(existing_element.has_value()) {
      throw redefinition_syntax_error(identifier_cursor.get_location(), name,
        existing_element->get_location());
    }
    if(c.is_empty()) {
      return nullptr;
    }
    require_assignment(c);
    auto initializer = parse_expression(c);
    if(initializer == nullptr) {
      return nullptr;
    }
    auto expression = std::make_unique<let_expression>(name,
      initializer->get_evaluation_type(), std::move(initializer));
    m_scopes.back()->add(element(std::make_shared<variable>(
      name, expression->get_evaluation_type()),
      identifier_cursor.get_location()));
    cursor = c;
    return expression;
  }

  inline std::unique_ptr<literal_expression> syntax_parser::
      parse_literal_expression(token_iterator& cursor) {
    if(cursor.is_empty()) {
      return nullptr;
    }
    return std::visit(
      [&] (auto&& value) -> std::unique_ptr<literal_expression> {
        using T = std::decay_t<decltype(value)>;
        if constexpr(std::is_same_v<T, literal>) {
          auto expression = std::make_unique<literal_expression>(value);
          ++cursor;
          return expression;
        }
        return nullptr;
      },
      cursor->get_instance());
  }

  inline std::unique_ptr<variable_expression>
      syntax_parser::parse_variable_expression(token_iterator& cursor) {
    auto c = cursor;
    auto name = try_parse_identifier(c);
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
      return std::make_unique<variable_expression>(*v);
    }
    return nullptr;
  }

  inline std::unique_ptr<expression> syntax_parser::parse_expression_term(
      token_iterator& cursor) {
    if(auto node = parse_literal_expression(cursor)) {
      return node;
    } else if(auto node = parse_let_expression(cursor)) {
      return node;
    } else if(auto node = parse_variable_expression(cursor)) {
      return node;
    } else if(auto node = parse_if_expression(cursor)) {
      return node;
    }
    return nullptr;
  }

  inline std::unique_ptr<expression> syntax_parser::parse_expression(
      token_iterator& cursor) {
    struct op_token {
      op m_op;
      location m_location;
    };
    std::deque<std::unique_ptr<expression>> expressions;
    std::stack<op_token> operators;
    auto build_call_expression =
      [&] (const op_token& o) {
        auto arity = get_arity(o.m_op);
        if(static_cast<int>(expressions.size()) < arity) {
          throw arity_syntax_error(o.m_location, expressions.size(), o.m_op);
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
        auto& function_name = get_function_name(o.m_op);
        auto function = resolve_overload(get_scope(), function_name,
          parameters, o.m_location);
        auto return_type = function->get_signature()->get_return_type();
        auto call = std::make_unique<call_expression>(
          std::make_unique<variable_expression>(std::move(function)),
          std::move(parameters), return_type);
        expressions.push_back(std::move(call));
      };
    auto c = cursor;
    enum class parse_mode {
      TERM,
      OPERATOR
    };
    auto mode = parse_mode::TERM;
    while(!c.is_empty()) {
      if(mode == parse_mode::TERM) {
        if(is_terminal(*c)) {
          break;
        } else if(match(*c, punctuation::mark::OPEN_BRACKET)) {
          operators.push({op::OPEN_BRACKET, c.get_location()});
          ++c;
        } else if(auto node = parse_expression_term(c)) {
          expressions.push_back(std::move(node));
          mode = parse_mode::OPERATOR;
        } else {
          break;
        }
      } else {
        if(c->get_type() == token::type::OPERATION) {
          auto o = get_binary_op(std::get<operation>(c->get_instance()));
          while(!operators.empty() &&
              (operators.top().m_op != op::OPEN_BRACKET &&
              operators.top().m_op != op::CLOSE_BRACKET &&
              (get_precedence(operators.top().m_op) > get_precedence(o) ||
              get_precedence(operators.top().m_op) == get_precedence(o) &&
              get_associativity(o) == associativity::LEFT_TO_RIGHT))) {
            build_call_expression(operators.top());
            operators.pop();
          }
          operators.push({o, c.get_location()});
          ++c;
          mode = parse_mode::TERM;
        } else if(match(*c, punctuation::mark::CLOSE_BRACKET)) {
          auto found_open_bracket = false;
          while(!operators.empty()) {
            auto o = operators.top();
            operators.pop();
            if(o.m_op == op::OPEN_BRACKET) {
              found_open_bracket = true;
              break;
            } else {
              build_call_expression(o);
            }
          }
          ++c;
          if(!found_open_bracket) {
            throw unmatched_bracket_syntax_error(c.get_location(),
              punctuation::mark::CLOSE_BRACKET);
          }
        } else {
          break;
        }
      }
    }
    while(!operators.empty()) {
      auto o = operators.top();
      operators.pop();
      if(o.m_op == op::OPEN_BRACKET || o.m_op == op::CLOSE_BRACKET) {
        auto bracket =
          [&] {
            if(o.m_op == op::OPEN_BRACKET) {
              return punctuation::mark::OPEN_BRACKET;
            }
            return punctuation::mark::CLOSE_BRACKET;
          }();
        throw unmatched_bracket_syntax_error(o.m_location, bracket);
      }
      build_call_expression(o);
    }
    if(expressions.empty()) {
      return nullptr;
    }
    auto e = std::move(expressions.front());
    expressions.pop_front();
    assert(expressions.empty());
    cursor = c;
    return e;
  }
}

#endif

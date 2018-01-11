#ifndef MAYLEE_TYPE_CHECK_HPP
#define MAYLEE_TYPE_CHECK_HPP
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>
#include "maylee/data_types/function_data_type.hpp"
#include "maylee/data_types/tuple_data_type.hpp"
#include "maylee/semantics/scope.hpp"
#include "maylee/syntax/syntax_nodes.hpp"
#include "maylee/syntax/syntax_node_visitor.hpp"

namespace maylee {
  class type_checker : private syntax_node_visitor {
    public:
      type_checker();

      void type_check(const std::vector<std::unique_ptr<syntax_node>>& nodes);

      std::shared_ptr<data_type> get_data_type(const syntax_node& node);

    private:
      std::shared_ptr<data_type> m_result;
      std::stack<std::unique_ptr<scope>> m_scopes;
      std::unordered_map<std::string, std::shared_ptr<data_type>> m_data_types;
      std::stack<std::vector<std::shared_ptr<data_type>>> m_return_types;

      const scope& get_scope() const;
      scope& get_scope();
      void push_scope();
      void pop_scope();
      std::shared_ptr<data_type> eval_type_expression(const expression& e);
      virtual void visit(const block_statement& node) override final;
      virtual void visit(const call_expression& node) override final;
      virtual void visit(const literal_expression& node) override final;
      virtual void visit(const function_definition& node) override final;
      virtual void visit(const return_statement& node) override final;
  };

  inline type_checker::type_checker() {
    m_scopes.push(std::make_unique<scope>());
    populate_global_scope(*m_scopes.top());
  }

  inline void type_checker::type_check(
      const std::vector<std::unique_ptr<syntax_node>>& nodes) {
    for(auto& node : nodes) {
      node->apply(*this);
    }
  }

  inline std::shared_ptr<data_type> type_checker::get_data_type(
      const syntax_node& node) {
    m_result.reset();
    node.apply(*this);
    return m_result;
  }

  inline const scope& type_checker::get_scope() const {
    return *m_scopes.top();
  }

  inline scope& type_checker::get_scope() {
    return *m_scopes.top();
  }

  inline void type_checker::push_scope() {
    auto s = std::make_unique<scope>(m_scopes.top().get());
    m_scopes.push(std::move(s));
  }

  inline void type_checker::pop_scope() {
    m_scopes.pop();
  }

  inline std::shared_ptr<data_type> type_checker::eval_type_expression(
      const expression& e) {
    if(auto t = dynamic_cast<const type_name_expression*>(&e)) {
      auto type = std::dynamic_pointer_cast<data_type>(
        get_scope().find(t->get_name()));
      if(type != nullptr) {
        return type;
      }
    }
    return nullptr;
  }

  inline void type_checker::visit(const block_statement& node) {
    push_scope();
    for(auto& statement : node.get_statements()) {
      statement->apply(*this);
    }
    pop_scope();
  }

  inline void type_checker::visit(const call_expression& node) {
    std::vector<std::shared_ptr<data_type>> parameter_types;
    for(auto& parameter : node.get_parameters()) {
      parameter_types.push_back(get_data_type(*parameter));
    }
    if(auto v = dynamic_cast<const variable_expression*>(
        &node.get_callable())) {
      auto f = get_scope().find(v->get_name(), parameter_types);
      if(f == nullptr) {
        // TODO
      }
      m_result = f->get_signature()->get_return_type();
      return;
    }
    // TODO
  }

  inline void type_checker::visit(const function_definition& node) {
    std::vector<function_data_type::parameter> parameters;
    for(auto& parameter : node.get_parameters()) {
      parameters.push_back({parameter.m_name,
        eval_type_expression(*parameter.m_type)});
    }
    m_return_types.push({});
    node.get_body().apply(*this);
    std::shared_ptr<data_type> return_type;
    if(m_return_types.top().empty()) {
      return_type = tuple_data_type::get_void();
    } else {
    }
    m_data_types[node.get_name()] = std::make_shared<function_data_type>(
      std::move(parameters), std::move(return_type));
  }

  inline void type_checker::visit(const literal_expression& node) {
    m_result = node.get_literal().get_type();
  }

  inline void type_checker::visit(const return_statement& node) {
    auto type = get_data_type(node.get_result());
    m_return_types.top().push_back(type);
  }
}

#endif

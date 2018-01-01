#ifndef MAYLEE_BLOCK_STATEMENT_HPP
#define MAYLEE_BLOCK_STATEMENT_HPP
#include <memory>
#include <utility>
#include <vector>
#include "maylee/syntax/scope.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node.hpp"

namespace maylee {

  //! Wraps multiple statements executed in sequence into one single statement.
  class block_statement : public syntax_node {
    public:

      //! Constructs a block statement.
      /*!
        \param scope The scope introduced by this block.
        \param statements The statements belonging to this block.
      */
      block_statement(std::unique_ptr<scope> scope,
        std::vector<std::unique_ptr<syntax_node>> statements);

      //! Returns the scoped introduced by this block.
      const scope& get_scope() const;

      //! Returns the statements belonging to this block.
      const std::vector<std::unique_ptr<syntax_node>>& get_statements() const;

    private:
      std::unique_ptr<scope> m_scope;
      std::vector<std::unique_ptr<syntax_node>> m_statements;
  };

  inline block_statement::block_statement(std::unique_ptr<scope> scope,
      std::vector<std::unique_ptr<syntax_node>> statements)
      : m_scope(std::move(scope)),
        m_statements(std::move(statements)) {}

  inline const scope& block_statement::get_scope() const {
    return *m_scope;
  }

  inline const std::vector<std::unique_ptr<syntax_node>>&
      block_statement::get_statements() const {
    return m_statements;
  }
}

#endif

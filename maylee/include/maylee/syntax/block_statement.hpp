#ifndef MAYLEE_BLOCK_STATEMENT_HPP
#define MAYLEE_BLOCK_STATEMENT_HPP
#include <memory>
#include <utility>
#include <vector>
#include "maylee/syntax/scope.hpp"
#include "maylee/syntax/statement.hpp"
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! Wraps multiple statements executed in sequence into one single statement.
  class block_statement : public statement {
    public:

      //! Constructs a block statement.
      /*!
        \param scope The scope introduced by this block.
        \param statements The statements belonging to this block.
      */
      block_statement(std::unique_ptr<scope> scope,
        std::vector<std::unique_ptr<statement>> statements);

      //! Returns the scoped introduced by this block.
      const scope& get_scope() const;

      //! Returns the statements belonging to this block.
      const std::vector<std::unique_ptr<statement>>& get_statements() const;

    private:
      std::unique_ptr<scope> m_scope;
      std::vector<std::unique_ptr<statement>> m_statements;
  };

  inline block_statement::block_statement(std::unique_ptr<scope> scope,
      std::vector<std::unique_ptr<statement>> statements)
      : m_scope(std::move(scope)),
        m_statements(std::move(statements)) {}

  inline const scope& block_statement::get_scope() const {
    return *m_scope;
  }

  inline const std::vector<std::unique_ptr<statement>>&
      block_statement::get_statements() const {
    return m_statements;
  }
}

#endif

#ifndef MAYLEE_BLOCK_STATEMENT_HPP
#define MAYLEE_BLOCK_STATEMENT_HPP
#include <memory>
#include <utility>
#include <vector>
#include "maylee/syntax/statement.hpp"
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! Wraps multiple statements executed in sequence into one single statement.
  class block_statement : public statement {
    public:

      //! Constructs a block statement.
      /*!
        \param statements The statements belonging to this block.
      */
      block_statement(std::vector<std::unique_ptr<statement>> statements);

      //! Returns the statements belonging to this block.
      const std::vector<std::unique_ptr<statement>>& get_statements() const;

    private:
      std::vector<std::unique_ptr<statement>> m_statements;
  };

  inline block_statement::block_statement(
      std::vector<std::unique_ptr<statement>> statements)
      : m_statements(std::move(statements)) {}

  inline const std::vector<std::unique_ptr<statement>>&
      block_statement::get_statements() const {
    return m_statements;
  }
}

#endif

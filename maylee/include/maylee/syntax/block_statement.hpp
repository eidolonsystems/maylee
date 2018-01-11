#ifndef MAYLEE_BLOCK_STATEMENT_HPP
#define MAYLEE_BLOCK_STATEMENT_HPP
#include <memory>
#include <utility>
#include <vector>
#include "maylee/syntax/statement.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node_visitor.hpp"

namespace maylee {

  //! Wraps multiple statements executed in sequence into one single statement.
  class block_statement : public statement {
    public:

      //! Constructs a block statement.
      /*!
        \param l The location of the start of the statement, typically a COLON.
        \param statements The statements belonging to this block.
      */
      block_statement(location l,
        std::vector<std::unique_ptr<statement>> statements);

      //! Returns the statements belonging to this block.
      const std::vector<std::unique_ptr<statement>>& get_statements() const;

      void apply(syntax_node_visitor& visitor) const override final;

    private:
      std::vector<std::unique_ptr<statement>> m_statements;
  };

  inline block_statement::block_statement(location l,
      std::vector<std::unique_ptr<statement>> statements)
      : statement(std::move(l)),
        m_statements(std::move(statements)) {}

  inline const std::vector<std::unique_ptr<statement>>&
      block_statement::get_statements() const {
    return m_statements;
  }

  inline void block_statement::apply(syntax_node_visitor& visitor) const {
    visitor.visit(*this);
  }

  inline void syntax_node_visitor::visit(const block_statement& node) {
    visit(static_cast<const syntax_node&>(node));
  }
}

#endif

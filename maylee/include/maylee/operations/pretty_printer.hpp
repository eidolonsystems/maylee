#ifndef MAYLEE_PRETTY_PRINTER_HPP
#define MAYLEE_PRETTY_PRINTER_HPP
#include <iostream>
#include "maylee/syntax/syntax_nodes.hpp"
#include "maylee/syntax/syntax_node_visitor.hpp"

namespace maylee {
namespace details {
  class pretty_print_visitor : private syntax_node_visitor {
    public:
      void operator ()(const syntax_node& node, std::ostream& out) {
        m_indent_level = 0;
        m_out = &out;
        node.apply(*this);
      }

      virtual void visit(const assignment_statement& node) override final {
        node.get_destination().apply(*this);
        *m_out << " = ";
        node.get_value().apply(*this);
      }

      virtual void visit(const block_statement& node) override final {
        ++m_indent_level;
        for(auto& statement : node.get_statements()) {
          indent();
          statement->apply(*this);
          *m_out << "\n";
        }
        --m_indent_level;
      }

      virtual void visit(const call_expression& node) override final {
        node.get_callable().apply(*this);
        *m_out << '(';
        auto is_first = true;
        for(auto& parameter : node.get_parameters()) {
          if(!is_first) {
            *m_out << ", ";
          } else {
            is_first = false;
          }
          parameter->apply(*this);
        }
        *m_out << ')';
      }

      virtual void visit(const function_definition& node) override final {
        *m_out << "def " << node.get_name() << '(';
        auto is_first = true;
        for(auto& parameter : node.get_parameters()) {
          if(!is_first) {
            *m_out << ", ";
          } else {
            is_first = false;
          }
          *m_out << parameter.m_name << ": ";
          parameter.m_type->apply(*this);
        }
        *m_out << "):\n";
        node.get_body().apply(*this);
        indent();
        *m_out << "end";
      }

      virtual void visit(const if_statement& node) override final {
        *m_out << "if ";
        node.get_condition().apply(*this);
        *m_out << ":\n";
        node.get_consequent().apply(*this);
        indent();
        *m_out << "else:\n";
        node.get_alternative().apply(*this);
        indent();
        *m_out << "end";
      }

      virtual void visit(const let_expression& node) override final {
        *m_out << "let " << node.get_name() << " = ";
        node.get_initializer().apply(*this);
      }

      virtual void visit(const literal_expression& node) override final {
        if(*node.get_literal().get_type() ==
            *string_lit_data_type::get_instance()) {
          *m_out << '"' << node.get_literal().get_value() << '"';
        } else {
          *m_out << node.get_literal().get_value();
        }
      }

      virtual void visit(const return_statement& node) override final {
        *m_out << "return ";
        node.get_result().apply(*this);
      }

      virtual void visit(const type_name_expression& node) override final {
        *m_out << node.get_name();
      }

      virtual void visit(const variable_expression& node) override final {
        *m_out << node.get_name();
      }

      virtual void visit(const void_expression& node) override final {
        *m_out << "()";
      }

    private:
      int m_indent_level;
      std::ostream* m_out;

      void indent() {
        for(auto i = 0; i < m_indent_level; ++i) {
          *m_out << "  ";
        }
      }
  };
}

  //! Pretty prints a syntax node to an output stream.
  /*!
    \param node The syntax node to print.
    \param out The output stream to print to.
  */
  inline void pretty_print(const syntax_node& node, std::ostream& out) {
    details::pretty_print_visitor()(node, out);
  }

  //! Pretty prints a syntax node to stdout.
  /*!
    \param node The syntax node to print.
  */
  inline void pretty_print(const syntax_node& node) {
    pretty_print(node, std::cout);
  }
}

#endif

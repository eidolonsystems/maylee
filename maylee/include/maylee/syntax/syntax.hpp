#ifndef MAYLEE_SYNTAX_HPP
#define MAYLEE_SYNTAX_HPP

namespace maylee {
  class assignment_statement;
  class block_statement;
  class call_expression;
  class expression;
  class function_definition;
  class function_not_found_syntax_error;
  class function_parameter_redefinition_syntax_error;
  class if_statement;
  class let_expression;
  class literal_expression;
  enum class op;
  class redefinition_syntax_error;
  class return_statement;
  class statement;
  enum class syntax_error_code;
  class syntax_error;
  class syntax_node;
  class syntax_node_visitor;
  class syntax_parser;
  class terminal_node;
  class token_iterator;
  class type_name_expression;
  class unmatched_bracket_syntax_error;
  class variable_expression;
  class void_expression;
}

#endif

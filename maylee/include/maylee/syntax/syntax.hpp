#ifndef MAYLEE_SYNTAX_HPP
#define MAYLEE_SYNTAX_HPP

namespace maylee {
  class block_statement;
  class call_expression;
  class element;
  class expression;
  class function;
  class function_not_found_syntax_error;
  class if_statement;
  class let_expression;
  class literal_expression;
  enum class op;
  class redefinition_syntax_error;
  class scope;
  class statement;
  enum class syntax_error_code;
  class syntax_error;
  class syntax_node;
  class syntax_parser;
  class terminal_node;
  class token_iterator;
  class type_expression;
  class unmatched_bracket_syntax_error;
  class variable;
  class variable_expression;
  class void_expression;
}

#endif

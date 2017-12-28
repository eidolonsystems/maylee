#ifndef MAYLEE_SCOPE_HPP
#define MAYLEE_SCOPE_HPP
#include <memory>
#include <optional>
#include <string_view>
#include <unordered_map>
#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/data_types/char_data_type.hpp"
#include "maylee/data_types/float_data_type.hpp"
#include "maylee/data_types/scalar_data_type.hpp"
#include "maylee/data_types/size_data_type.hpp"
#include "maylee/syntax/element.hpp"
#include "maylee/syntax/function_not_found_syntax_error.hpp"
#include "maylee/syntax/ops.hpp"
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! Scopes are used to store and look-up named language constructs such as
  //! variables, data types, functions, etc...
  class scope {
    public:

      //! Constructs an empty global scope.
      scope();

      //! Constructs a child scope.
      /*!
        \param parent The parent scope.
      */
      scope(const scope* parent);

      //! Tests if an element with a specified name is contained within this
      //! scope (that is directly within this scope, not a parent scope).
      bool contains(const std::string& name) const;

      //! Finds an element accessible from within this scope (ie. contained
      //! within this scope or a parent scope).
      std::optional<element> find(const std::string& name) const;

      //! Finds 

      //! Finds an element within this scope (ie. contained strictly within this
      //! scope, not a parent scope).
      std::optional<element> find_within(const std::string& name) const;

      //! Adds an element to this scope.
      /*!
        \param element The element to add.
        \return <code>true</code> iff the element was added, otherwise an
                element with the same name already exists.
      */
      bool add(element element);

    private:
      const scope* m_parent;
      std::unordered_map<std::string, element> m_elements;

      scope(const scope&) = delete;
      scope& operator =(const scope&) = delete;
  };

  //! Populates a scope with all global/built-in elements.
  /*!
    \param scope The scope to populate.
  */
  inline void populate_global_scope(scope& scope) {
    scope.add(element(bool_data_type::get_instance(), location::global()));
    scope.add(element(char_data_type::get_instance(), location::global()));
    scope.add(element(float_data_type::get_float32(), location::global()));
    scope.add(element(float_data_type::get_float64(), location::global()));
    scope.add(element(scalar_data_type::get_int8(), location::global()));
    scope.add(element(scalar_data_type::get_int16(), location::global()));
    scope.add(element(scalar_data_type::get_int32(), location::global()));
    scope.add(element(scalar_data_type::get_int64(), location::global()));
    scope.add(element(scalar_data_type::get_uint8(), location::global()));
    scope.add(element(scalar_data_type::get_uint16(), location::global()));
    scope.add(element(scalar_data_type::get_uint32(), location::global()));
    scope.add(element(scalar_data_type::get_uint64(), location::global()));
    scope.add(element(size_data_type::get_instance(), location::global()));
    scope.add(element(get_add_function(*scalar_data_type::get_int32(),
      *scalar_data_type::get_int32()), location::global()));
    scope.add(element(get_subtract_function(*scalar_data_type::get_int32(),
      *scalar_data_type::get_int32()), location::global()));
    scope.add(element(get_multiply_function(*scalar_data_type::get_int32(),
      *scalar_data_type::get_int32()), location::global()));
    scope.add(element(get_divide_function(*scalar_data_type::get_int32(),
      *scalar_data_type::get_int32()), location::global()));
  }

  //! Given a function name and a list of parameters, finds the correct
  //! function overload to apply.
  /*!
    \param s The scope to search.
    \param name The name of the function.
    \param parameters The parameters to apply.
    \param l The location of the function call.
    \return The correct function overload accessible from scope <i>s</i> with
            the specified name applied to the specified parameters.
  */
  inline std::shared_ptr<function> resolve_overload(const scope& s,
      const std::string& name,
      const std::vector<std::unique_ptr<expression>>& parameters,
      const location& l) {
    auto e = s.find(name);
    if(!e.has_value()) {
      throw function_not_found_syntax_error(l, name);
    }
    if(auto v = std::get_if<std::shared_ptr<variable>>(&e->get_instance())) {
      auto f = std::dynamic_pointer_cast<function>(*v);
      if(f == nullptr) {
        throw syntax_error(syntax_error_code::EXPRESSION_NOT_CALLABLE, l);
      }
      return f;
    }
    throw syntax_error(syntax_error_code::EXPRESSION_NOT_CALLABLE, l);
  }

  inline scope::scope()
      : m_parent(nullptr) {}

  inline scope::scope(const scope* parent)
      : m_parent(parent) {}

  inline bool scope::contains(const std::string& name) const {
    return m_elements.count(name) == 1;
  }

  inline std::optional<element> scope::find(const std::string& name) const {
    auto element = m_elements.find(name);
    if(element == m_elements.end()) {
      if(m_parent == nullptr) {
        return std::nullopt;
      }
      return m_parent->find(name);
    }
    return element->second;
  }

  inline std::optional<element> scope::find_within(
      const std::string& name) const {
    auto element = m_elements.find(name);
    if(element == m_elements.end()) {
      return std::nullopt;
    }
    return element->second;
  }

  inline bool scope::add(element element) {
    return m_elements.try_emplace(
      element.get_name(), std::move(element)).second;
  }
}

#endif

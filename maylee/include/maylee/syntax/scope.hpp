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

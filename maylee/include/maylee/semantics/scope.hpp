#ifndef MAYLEE_SCOPE_HPP
#define MAYLEE_SCOPE_HPP
#include <memory>
#include <unordered_map>
#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/data_types/char_data_type.hpp"
#include "maylee/data_types/float_data_type.hpp"
#include "maylee/data_types/scalar_data_type.hpp"
#include "maylee/data_types/size_data_type.hpp"
#include "maylee/semantics/element.hpp"
#include "maylee/semantics/function.hpp"
#include "maylee/semantics/semantics.hpp"
#include "maylee/syntax/ops.hpp"

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
      std::shared_ptr<element> find(const std::string& name) const;

      //! Finds 

      //! Finds an element within this scope (ie. contained strictly within this
      //! scope, not a parent scope).
      std::shared_ptr<element> find_within(const std::string& name) const;

      //! Adds an element to this scope.
      /*!
        \param element The element to add.
        \return <code>true</code> iff the element was added, otherwise an
                element with the same name already exists.
      */
      bool add(std::shared_ptr<element> element);

    private:
      const scope* m_parent;
      std::unordered_map<std::string, std::shared_ptr<element>> m_elements;

      scope(const scope&) = delete;
      scope& operator =(const scope&) = delete;
  };

  //! Populates a scope with all global/built-in elements.
  /*!
    \param scope The scope to populate.
  */
  inline void populate_global_scope(scope& scope) {
    scope.add(bool_data_type::get_instance());
    scope.add(char_data_type::get_instance());
    scope.add(float_data_type::get_float());
    scope.add(float_data_type::get_double());
    scope.add(scalar_data_type::get_sbyte());
    scope.add(scalar_data_type::get_short());
    scope.add(scalar_data_type::get_int());
    scope.add(scalar_data_type::get_long());
    scope.add(scalar_data_type::get_byte());
    scope.add(scalar_data_type::get_ushort());
    scope.add(scalar_data_type::get_uint());
    scope.add(scalar_data_type::get_ulong());
    scope.add(size_data_type::get_instance());
    scope.add(std::make_shared<function>(location::global(), "add"));
    scope.add(std::make_shared<function>(location::global(), "subtract"));
    scope.add(std::make_shared<function>(location::global(), "multiply"));
    scope.add(std::make_shared<function>(location::global(), "divide"));
  }

  inline scope::scope()
      : m_parent(nullptr) {}

  inline scope::scope(const scope* parent)
      : m_parent(parent) {}

  inline bool scope::contains(const std::string& name) const {
    return m_elements.count(name) == 1;
  }

  inline std::shared_ptr<element> scope::find(const std::string& name) const {
    auto element = m_elements.find(name);
    if(element == m_elements.end()) {
      if(m_parent == nullptr) {
        return nullptr;
      }
      return m_parent->find(name);
    }
    return element->second;
  }

  inline std::shared_ptr<element> scope::find_within(
        const std::string& name) const {
    auto element = m_elements.find(name);
    if(element == m_elements.end()) {
      return nullptr;
    }
    return element->second;
  }

  inline bool scope::add(std::shared_ptr<element> element) {
    return m_elements.try_emplace(
      element->get_name(), std::move(element)).second;
  }
}

#endif

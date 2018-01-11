#ifndef MAYLEE_SCOPE_HPP
#define MAYLEE_SCOPE_HPP
#include <memory>
#include <unordered_map>
#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/data_types/char_data_type.hpp"
#include "maylee/data_types/float_data_type.hpp"
#include "maylee/data_types/function_data_type.hpp"
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

      //! Finds the specific function among an overloaded set.
      /*!
        \param name The name of the function to find.
        \param parameters The parameters being passed to the function.
        \return The function matching the specified <i>name</i> and
                <i>parameters</i>.
      */
      std::shared_ptr<function> find(const std::string& name,
        const std::vector<std::shared_ptr<data_type>>& parameters) const;

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

      //! Adds a function to this scope.
      /*!
        \param f The function to add.
        \return <code>true</code> iff the element was added, otherwise a
                function with the same signature already exists.
      */
      bool add(std::shared_ptr<function> f);

    private:
      const scope* m_parent;
      std::unordered_map<std::string, std::shared_ptr<element>> m_elements;
      std::unordered_map<std::string, std::vector<std::shared_ptr<function>>>
        m_function_overloads;

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
    scope.add(std::make_shared<function>(location::global(), "add",
      std::make_shared<function_data_type>(
      std::vector<function_data_type::parameter>(
        {{"left", scalar_data_type::get_int()},
         {"right", scalar_data_type::get_int()}}),
        scalar_data_type::get_int())));
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

  inline std::shared_ptr<function> scope::find(const std::string& name,
      const std::vector<std::shared_ptr<data_type>>& parameters) const {
    auto f = m_function_overloads.find(name);
    if(f == m_function_overloads.end()) {
      if(m_parent == nullptr) {
        return nullptr;
      }
      return m_parent->find(name, parameters);
    }
    auto& existing_overloads = f->second;
    for(auto& overload : existing_overloads) {
      auto& overload_signature = overload->get_signature();
      auto is_equal = true;
      if(parameters.size() == overload_signature->get_parameters().size()) {
        for(std::size_t i = 0; i < parameters.size(); ++i) {
          if(*parameters[i] !=
              *overload_signature->get_parameters()[i].m_type) {
            is_equal = false;
            break;
          }
        }
      } else {
        is_equal = false;
      }
      if(is_equal) {
        return overload;
      }
    }
    return nullptr;
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
    if(auto f = std::dynamic_pointer_cast<function>(element)) {
      return add(std::move(f));
    }
    return m_elements.try_emplace(
      element->get_name(), std::move(element)).second;
  }

  inline bool scope::add(std::shared_ptr<function> f) {
    auto& signature = f->get_signature();
    auto& existing_overloads = m_function_overloads[f->get_name()];
    for(auto& overload : existing_overloads) {
      auto& overload_signature = overload->get_signature();
      auto is_equal = true;
      if(signature->get_parameters().size() ==
          overload_signature->get_parameters().size()) {
        for(std::size_t i = 0; i < signature->get_parameters().size(); ++i) {
          if(*signature->get_parameters()[i].m_type !=
              *overload_signature->get_parameters()[i].m_type) {
            is_equal = false;
            break;
          }
        }
      } else {
        is_equal = false;
      }
      if(is_equal) {
        return false;
      }
    }
    auto existing_element = find(f->get_name());
    if(existing_element == nullptr) {
      m_elements.insert(std::make_pair(f->get_name(), f));
    } else if(std::dynamic_pointer_cast<function>(existing_element) ==
        nullptr) {
      return false;
    }
    existing_overloads.push_back(std::move(f));
    return true;
  }
}

#endif

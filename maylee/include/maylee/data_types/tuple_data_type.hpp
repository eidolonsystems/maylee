#ifndef MAYLEE_TUPLE_DATA_TYPE_HPP
#define MAYLEE_TUPLE_DATA_TYPE_HPP
#include <algorithm>
#include <memory>
#include <string>
#include <optional>
#include <utility>
#include <vector>
#include "maylee/data_types/data_type.hpp"

namespace maylee {

  //! A data type that stores multiple values accessible by name.
  class tuple_data_type : public data_type {
    public:

      //! Stores a member of a tuple.
      struct member {

        //! The name of the member.
        std::string m_name;

        //! The member's data type.
        std::shared_ptr<data_type> m_type;
      };

      //! Returns the void data type.
      static const std::shared_ptr<tuple_data_type>& get_void();

      //! Constructs a tuple data type.
      /*!
        \param members The tuples members.
      */
      tuple_data_type(std::vector<member> members);

      //! Returns the tuple's members.
      const std::vector<member>& get_members() const;

      //! Returns the member with a given name.
      /*!
        \param name The name of the tuple member.
        \return The member with the specified name.
      */
      const member* find_member(const std::string_view& name) const;

      const std::string& get_name() const override final;

    protected:
      bool is_equal(const data_type& rhs) const override final;

    private:
      std::vector<member> m_members;
      std::string m_name;
  };

  inline bool operator ==(const tuple_data_type::member& lhs,
      const tuple_data_type::member& rhs) {
    return lhs.m_name == rhs.m_name && *lhs.m_type == *rhs.m_type;
  }

  inline bool operator != (const tuple_data_type::member& lhs,
      const tuple_data_type::member& rhs) {
    return !(lhs == rhs);
  }

  inline const std::shared_ptr<tuple_data_type>& tuple_data_type::get_void() {
    static auto t = std::make_shared<tuple_data_type>(std::vector<member>());
    return t;
  }

  inline tuple_data_type::tuple_data_type(std::vector<member> members)
      : m_members(std::move(members)) {
    m_name = "(";
    auto is_first = true;
    for(auto& member : m_members) {
      if(!is_first) {
        m_name += ", ";
      } else {
        is_first = false;
      }
      m_name += member.m_type->get_name();
      if(!member.m_name.empty()) {
        m_name += " " + member.m_name;
      }
    }
    m_name += ")";
  }

  inline const std::vector<tuple_data_type::member>&
      tuple_data_type::get_members() const {
    return m_members;
  }

  inline const tuple_data_type::member* tuple_data_type::find_member(
      const std::string_view& name) const {
    auto m = std::find_if(m_members.begin(), m_members.end(),
      [&] (auto& member) {
        return member.m_name == name;
      });
    if(m == m_members.end()) {
      return nullptr;
    }
    return &*m;
  }

  inline const std::string& tuple_data_type::get_name() const {
    return m_name;
  }

  inline bool tuple_data_type::is_equal(const data_type& rhs) const {
    auto& t = static_cast<const tuple_data_type&>(rhs);
    return m_members == t.get_members();
  }
}

#endif

#ifndef MAYLEE_UNION_DATA_TYPE_HPP
#define MAYLEE_UNION_DATA_TYPE_HPP
#include <algorithm>
#include <cassert>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "maylee/data_types/data_type.hpp"

namespace maylee {

  //! A data type that represents a value that can be one of fixed set of data
  //! types.
  class union_data_type : public data_type {
    public:

      //! Returns the bottom data type.
      static std::shared_ptr<union_data_type> get_bottom();

      //! Constructs a union data type.
      /*!
        \param variants The data types that are represented by this union.
      */
      union_data_type(std::vector<std::shared_ptr<data_type>> variants);

      //! Returns the union's variants.
      const std::vector<std::shared_ptr<data_type>>& get_variants() const;

      const location& get_location() const override final;

      const std::string& get_name() const override final;

    protected:
      bool is_equal(const data_type& rhs) const override final;

    private:
      std::vector<std::shared_ptr<data_type>> m_variants;
      std::string m_name;
  };

  //! Constructs the appropriate union type from a list of variants.
  /*!
    \param variants The list of data types to represent by the union.
    \return If <i>variants</i> is empty then the bottom union type is returned.
            If <i>variants</i> consists of one unique data type then that
            data type is returned.
            Otherwise a union data type consisting of the unique data types in
            the list of <i>variants</i>.
  */
  inline std::shared_ptr<data_type> make_union_data_type(
      std::vector<std::shared_ptr<data_type>> variants) {
    if(variants.empty()) {
      return union_data_type::get_bottom();
    }
    auto remove_location = variants.end();
    for(auto i = variants.begin(); i != remove_location; ++i) {
      remove_location = std::min(remove_location,
        std::remove_if(i + 1, remove_location,
        [&] (auto& type) {
          return *type == **i;
        }));
    }
    variants.erase(remove_location, variants.end());
    if(variants.size() == 1) {
      return variants.front();
    }
    return std::make_shared<union_data_type>(std::move(variants));
  }

  inline std::shared_ptr<union_data_type> union_data_type::get_bottom() {
    static auto t = std::make_shared<union_data_type>(
      std::vector<std::shared_ptr<data_type>>());
    return t;
  }

  inline union_data_type::union_data_type(
      std::vector<std::shared_ptr<data_type>> variants)
      : m_variants(std::move(variants)) {
    assert(m_variants.size() != 1);
    if(m_variants.empty()) {
      m_name = "(|)";
    } else {
      m_name = "(";
      auto is_first = true;
      for(auto& variant : m_variants) {
        if(!is_first) {
          m_name += " | ";
        } else {
          is_first = false;
        }
        m_name += variant->get_name();
      }
      m_name += ")";
    }
  }

  inline const std::vector<std::shared_ptr<data_type>>&
      union_data_type::get_variants() const {
    return m_variants;
  }

  inline const location& union_data_type::get_location() const {
    return location::global();
  }

  inline const std::string& union_data_type::get_name() const {
    return m_name;
  }

  inline bool union_data_type::is_equal(const data_type& rhs) const {
    auto& t = static_cast<const union_data_type&>(rhs);
    if(m_variants.size() != t.get_variants().size()) {
      return false;
    }
    for(std::size_t i = 0; i != m_variants.size(); ++i) {
      if(*m_variants[i] != *t.get_variants()[i]) {
        return false;
      }
    }
    return true;
  }
}

#endif

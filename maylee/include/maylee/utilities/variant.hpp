#ifndef MAYLEE_VARIANT_HPP
#define MAYLEE_VARIANT_HPP
#include <cstdint>
#include "maylee/utilities/utilities.hpp"

namespace maylee {
namespace details {
  template<typename T1, typename T2>
  union variant_union {
    T1 m_first;
    T2 m_second;

    variant_union() {}
    variant_union(const variant_union&) = delete;
    variant_union& operator =(const variant_union&) = delete;
    ~variant_union() {}
  };

  template<typename... T>
  struct get_variant_union;

  template<typename T>
  struct get_variant_union<T> {
    using type = T;
  };

  template<typename T1, typename... T2>
  struct get_variant_union<T1, T2...> {
    using type = variant_union<T1, typename get_variant_union<T2...>::type>;
  };

  template<typename T, typename F, typename Enabled = void>
  struct call_variant {

  };

  template<typename T, typename F>
  struct call_variant<T, F, template<typename F,
      std::enable_if_t<decltype(std::declval<F&&>()(decl
 {
    decltype(auto) operator()(
  };

  template<typename... T>
  struct apply_variant;

  template<typename T1, typename... T>
  struct apply_variant<T1, T...> {
    template<typename... F>
    decltype(auto) operator()(std::uint8_t& which,
        typename get_variant_union<T1, T...>::type& value, F&& f) const {
      if(which == 0) {
        return f(value.m_first);
      }
      --which;
      return apply_variant<T...>()(which, value.m_second, std::forward<F>(f));
    }
  };

  template<typename T>
  struct apply_variant<T> {
    template<typename F>
    decltype(auto) operator()(std::uint8_t& which, T& value, F&& f) const {
      if(which == 0) {
        return f(value);
      }
      throw 5;
    }
  };
}

  template<typename... T>
  class variant {
    public:
      variant();

      ~variant();

      template<typename... F>
      decltype(auto) apply(F&&... f) {
        auto which = m_which;
        return details::apply_variant<T...>()(which, m_value,
          std::forward<F>(f)...);
      }

    private:
      std::uint8_t m_which;
      typename details::get_variant_union<T...>::type m_value;
  };

  template<typename... T>
  variant<T...>::variant()
      : m_which(sizeof...(T)) {}

  template<typename... T>
  variant<T...>::~variant() {
    if(m_which == sizeof...(T)) {
      return;
    }
  }
}

#endif

#ifndef MAYLEE_VARIANT_HPP
#define MAYLEE_VARIANT_HPP
#include <cstdint>
#include <type_traits>
#include "maylee/utilities/utilities.hpp"

namespace maylee {
namespace details {
  template<typename T1, typename T2>
  union variant_union {
    T1 m_first;
    T2 m_second;
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

  template<std::uint8_t W, typename... T>
  struct variant_assign;

  template<std::uint8_t W, typename T>
  struct variant_assign<W, T> {
    void destroy(std::uint8_t which, void* lhs) const {
      if(which == W) {
        return;
      }
      reinterpret_cast<T*>(lhs)->~T();
    }

    std::uint8_t assign(std::uint8_t which, void* lhs, const T& rhs) const {
      if(which != W) {
        new (lhs) T(rhs);
      } else {
        *reinterpret_cast<T*>(lhs) = rhs;
      }
      return W;
    }

    std::uint8_t assign(std::uint8_t which, void* lhs, T&& rhs) const {
      if(which != W) {
        new (lhs) T(std::move(rhs));
      } else {
        *reinterpret_cast<T*>(lhs) = std::move(rhs);
      }
      return W;
    }
  };

  template<std::uint8_t W, typename T1, typename... T>
  struct variant_assign<W, T1, T...> : variant_assign<W, T1>,
      variant_assign<W + 1, T...> {
    using variant_assign<W, T1>::destroy;
    using variant_assign<W, T1>::assign;
    using variant_assign<W + 1, T...>::destroy;
    using variant_assign<W + 1, T...>::assign;
  };

  template<typename... T>
  struct variant_apply;

  template<typename T1, typename... T>
  struct variant_apply<T1, T...> {
    template<typename F>
    decltype(auto) operator ()(std::uint8_t which,
        typename get_variant_union<T1, T...>::type& value, F&& f) const {
      if(which == 0) {
        std::cout << typeid(T1).name() << std::endl;
      } else {
        return variant_apply<T...>()(which - 1, value.m_second,
          std::forward<F>(f));
      }
    }
  };

  template<typename T>
  struct variant_apply<T> {
    template<typename F>
    decltype(auto) operator ()(std::uint8_t which, T& value, F&& f) const {
      if(which != 0) {
        std::cout << "faak" << std::endl;
      }
    }
  };
}

  template<typename... T>
  class variant {
    public:
      variant();

      template<typename U>
      variant(U&& value);

      ~variant();

      template<typename U>
      variant& operator =(const U& rhs) {
        m_which = details::variant_assign<0, T...>().assign(m_which, &m_value,
          rhs);
        return *this;
      }

      template<typename U>
      variant& operator =(U&& rhs) {
        m_which = details::variant_assign<0, T...>().assign(m_which, &m_value,
          std::forward<U>(rhs));
        return *this;
      }

      template<typename F>
      decltype(auto) apply(F&& f) {
//        details::variant_apply<T...>()(m_which, m_value, std::forward<F>(f));
      }

    private:
      using variant_union = typename details::get_variant_union<T...>::type;
      using storage = std::aligned_storage_t<sizeof(variant_union)>;
      std::uint8_t m_which;
      storage m_value;
  };

  template<typename... T>
  variant<T...>::variant() {}

  template<typename... T>
  template<typename U>
  variant<T...>::variant(U&& value)
      : m_which(sizeof...(T)) {
    *this = std::forward<U>(value);
  }

  template<typename... T>
  variant<T...>::~variant() {}
}

#endif

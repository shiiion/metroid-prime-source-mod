#pragma once

#include <type_traits>
#include <utility>

#include "freestanding.hh"
#include "mp2/rstl/utility.hh"

namespace rstl {

template <typename T>
class optional {
private:
   union alignas(T) storage_t {
      struct {
      } _dummy;
      T _val;
      storage_t() : _dummy() {}
      ~storage_t() {}
   };

   // Shortened with constexpr if
   template <typename Tp>
   static void destroy(Tp& v) {
      if constexpr (std::is_destructible_v<Tp> && !std::is_trivially_destructible_v<Tp>) {
         v.Tp::~Tp();
      }
   }

private:
   storage_t _storage;
   bool _assigned;

public:
   optional() : _assigned(false) {}

   void reset() {
      if (_assigned) {
         destroy(_storage._val);
         _assigned = false;
      }
   }

   optional& operator=(optional<T> const& other) {
      reset();
      _assigned = other._assigned;
      if (_assigned) {
         utility::placement_new(_storage._val, other._storage._val);
      }
      return *this;
   }

   optional& operator=(optional<T>&& other) {
      reset();
      _assigned = std::move(other._assigned);
      if (_assigned) {
         utility::placement_new(_storage._val, std::forward<T>(other._storage._val));
      }
      return *this;
   }

   optional& operator=(T const& assign) {
      reset();
      utility::placement_new(_storage._val, assign);
      _assigned = true;
      return *this;
   }

   optional& operator=(T&& assign) {
      reset();
      utility::placement_new(_storage._val, std::forward<T>(assign));
      _assigned = true;
      return *this;
   }

   constexpr operator bool() const { return _assigned; }
   constexpr T& operator*() { return _storage._val; }
   constexpr T const& operator*() const { return _storage._Val; }
   constexpr T* operator->() { return utility::addressof(_storage._val); }
   constexpr T const* operator->() const { return utility::addressof(_storage._val); }
};

}  // namespace rstl

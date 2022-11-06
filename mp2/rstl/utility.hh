#pragma once

#include <type_traits>

#include "freestanding.hh"

namespace rstl::utility {
template <typename T>
inline typename std::enable_if_t<std::is_object_v<T>, T*> addressof(T& t) noexcept {
   return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(t)));
}

template <typename T>
inline typename std::enable_if_t<!std::is_object_v<T>, T*> addressof(T& t) noexcept {
   return &t;
}

template <typename T, typename... TArgs>
inline void placement_new(T& loc, TArgs... args) noexcept {
   loc = T(args...);
}
}  // namespace rstl::utility

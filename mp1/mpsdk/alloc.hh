#pragma once

#include "util/func_caller.hh"

void* alloc(u32 size) {
   return call_func<void*, u32, char const*, char const*>(0x8031586c, size, "??(??)", nullptr);
}

template <typename T>
T* alloc_inst() {
   return static_cast<T*>(alloc(sizeof(T)));
}

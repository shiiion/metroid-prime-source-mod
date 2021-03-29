#pragma once

#include "util/func_caller.hh"

void* alloc(u32 size);
void free(void* ptr);

template <typename T>
T* alloc_inst() {
   return static_cast<T*>(alloc(sizeof(T)));
}

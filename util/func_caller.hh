#pragma once

#include "freestanding.hh"

template <typename TRet, typename... TArgs>
TRet call_func(uintptr_t func_address, TArgs... args) {
   using FuncType = TRet (*)(TArgs...);

   FuncType fn = reinterpret_cast<FuncType>(func_address);
   return fn(args...);
}

template <typename TRet, typename... TArgs>
TRet call_class_func(uintptr_t func_address, void* inst, TArgs... args) {
   using FuncType = TRet (*)(void*, TArgs...);

   FuncType fn = reinterpret_cast<FuncType>(func_address);
   return fn(inst, args...);
}

template <typename TRet, typename... TArgs>
TRet call_class_func(uintptr_t func_address, void const* inst, TArgs... args) {
   using FuncType = TRet (*)(void const*, TArgs...);

   FuncType fn = reinterpret_cast<FuncType>(func_address);
   return fn(inst, args...);
}

template <typename TRet, typename... TArgs>
TRet call_vfunc(void* inst, uint32_t index, TArgs... args) {
   uintptr_t* table_base = *reinterpret_cast<uintptr_t**>(inst);
   return call_class_func<TRet, TArgs...>(table_base[index + 2], inst, args...);
}

template <typename TRet, typename... TArgs>
TRet call_vfunc(void const* inst, uint32_t index, TArgs... args) {
   uintptr_t const* const table_base = *reinterpret_cast<uintptr_t const* const*>(inst);
   return call_class_func<TRet, TArgs...>(table_base[index + 2], inst, args...);
}
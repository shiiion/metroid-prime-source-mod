#include "mp1/mpsdk/alloc.hh"

void* alloc(u32 size) {
   return call_func<void*, u32, char const*, char const*>(0x8031586c, size, "??(??)", nullptr);
}

void free(void* ptr) {
   call_func<void, void*>(0x80315930, ptr);
}
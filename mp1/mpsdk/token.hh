#pragma once

#include "freestanding.hh"
#include "mp1/mpsdk/retro_types.hh"
#include "util/func_caller.hh"

// Details unimportant
class CObjectReference;

struct IObj {
   NO_INSTANTIATE(IObj);

   uintptr_t const* const vtable;
   void* obj_ptr;
};

class CToken {
   CObjectReference* object_ref;
   bool lock_held;

public:
   // May want to change this later, but we have little use now
   NO_INSTANTIATE(CToken);

   IObj* get_obj() { return call_class_func<IObj*>(0x80340e0c, this); }

   void lock() { call_class_func<void>(0x80340d84, this); }
   void remove_ref() { call_class_func<void>(0x80340dc8, this); }
   void unlock() { call_class_func<void>(0x80340d40, this); }
   ~CToken() { call_class_func<void, int>(0x80340e40, this, 0); }
};

template <typename T>
class TToken {
private:
   CToken inner;

public:
   NO_INSTANTIATE(TToken);

   T* get_obj() { return static_cast<T*>(inner.get_obj()->obj_ptr); }
   void lock() { inner.lock(); }
   void remove_ref() { inner.remove_ref(); }
   void unlock() { inner.unlock(); }
};

// only created this for padding and slight correctness, probably never need
// its special functionality
template <typename T>
struct TCachedToken : TToken<T> {
   T* obj_cache;

   NO_INSTANTIATE(TCachedToken);
};
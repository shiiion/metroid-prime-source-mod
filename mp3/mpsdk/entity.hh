#pragma once

#include "freestanding.hh"
#include "util/func_caller.hh"

struct UID {
  u32 uid;
};

class CEntity {
public:
   NO_INSTANTIATE(CEntity);
   UID const& get_unique_id() const { return uid; }

protected:
   uintptr_t const* const vtable; // 0
   s32 area_id; // 4
   UID uid; // 8
   uint8_t centity_unk0[0x30]; // 0xc -> 0x3c
};

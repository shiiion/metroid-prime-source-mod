#pragma once

#include "freestanding.hh"

#define GEN_GET_SET(name, type, off) \
   type get_##name() const { \
      return *get_off<type>(off); \
   } \
   void set_##name(type val) { \
      *get_off<type>(off) = val; \
   }

class CTweak {
protected:
   template <typename T>
   T* get_off(u32 offset) {
      return reinterpret_cast<T*>(reinterpret_cast<u8*>(this) + offset);
   }

   template <typename T>
   T const* get_off(u32 offset) const {
      return reinterpret_cast<T const*>(reinterpret_cast<u8 const*>(this) + offset);
   }
};

// Not filling this in fully for mp2
class CTweakPlayer : public CTweak {
public:
   NO_INSTANTIATE(CTweakPlayer);
   static CTweakPlayer* instance() { return **reinterpret_cast<CTweakPlayer***>(0x80418f44); }

   GEN_GET_SET(gravity, float, 0x104)
   GEN_GET_SET(gravboost_force, float, 0x168)
   GEN_GET_SET(eye_offset, float, 0x174)
};

class CTweakPowerup : public CTweak {
public:
   NO_INSTANTIATE(CTweakPowerup);
   static CTweakPowerup* instance() { return **reinterpret_cast<CTweakPowerup***>(0x80418f2c); }

   GEN_GET_SET(screwattack_leniency_z, float, 0x220)
};

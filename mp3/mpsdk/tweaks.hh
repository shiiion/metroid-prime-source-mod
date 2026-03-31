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

// Not filling this in fully for mp3
class CTweakPlayer : public CTweak {
public:
   NO_INSTANTIATE(CTweakPlayer);
   static CTweakPlayer* instance();

   GEN_GET_SET(gravity, float, 0x15c)
   GEN_GET_SET(eye_offset, float, 0x1cc)
   GEN_GET_SET(grapple_jump_time, float, 0x37c)
   GEN_GET_SET(grapple_jump_impulse, float, 0x378)
};

class CTweakGun : public CTweak {
public:
   NO_INSTANTIATE(CTweakGun);
   static CTweakGun* instance();

   GEN_GET_SET(missile_delay, float, 0x1e8)
};

class CTweakPowerup : public CTweak {
public:
   NO_INSTANTIATE(CTweakPowerup);
   static CTweakPowerup* instance();

   GEN_GET_SET(screwattack_leniency_z, float, 0x20c)
};

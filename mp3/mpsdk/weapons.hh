#pragma once

#include "mp3/mpsdk/actor.hh"

enum class EProjectileAttrib {
   None = 0,
   Charged = (1 << 2),
};

enum class EWeaponType {
   None = -1,
   Power = 0,
   Missile = 4,
   IceMissile = 5,
   PhazonMissile = 6,
};

constexpr bool is_missile(EWeaponType ty) {
  return ty == EWeaponType::Missile ||
         ty == EWeaponType::IceMissile ||
         ty == EWeaponType::PhazonMissile;
}

class CWeapon : public CActor {
protected:
   u32 owner_id; // 154
   EWeaponType weapon_type; // 158
   uint8_t cweapon_unk0[0x8c]; // 15c -> 1e8
   float cur_time; // 1e8

public:
   EWeaponType get_weapon_type() const { return weapon_type; }
   float get_alive_time() const { return cur_time; }
};

class CGameProjectile;
struct CProjectileWeapon {
   uintptr_t const* const vtable; // 0
   uint8_t cprojweapon_unk0[0x34]; // 4 -> 38
   vec3 velocity; // 38
   uint8_t cprojweapon_unk1[0x9c]; // 44 -> e0
   double cur_time; // e0
   uint8_t cprojectileweapon_unk4[0x68]; // e8 -> 150

   CGameProjectile* owner() {
      return reinterpret_cast<CGameProjectile*>(reinterpret_cast<uint8_t*>(this) - 0x288);
   }
};

class CGameProjectile : public CWeapon {
protected:
   uint8_t cgameprojectile_unk0[0x9c]; // 1ec -> 288
   CProjectileWeapon projectile_vars; // 288 -> 3d8
   uint8_t cgameprojectile_unk1[0xcc]; // 3d8 -> 4a4
   bool projectile_active : 1; // 4a4

public:
   void set_speed(float speed);
   void multiply_speed(float multiplier);
   bool is_projectile_active() const { return projectile_active; }
};

class CEnergyProjectile : public CGameProjectile {
protected:
   uint8_t cenergyprojectile_unk0[0x8]; // 4a8 -> 4b0
   vec3 dir; // 4b0
   float mag; // 4bc
   uint8_t cenergyprojectile_unk1[0x209]; // 4c0 -> 6c9
   // added this to check if we've detected an explosion yet
   bool detected_explosion : 1; // 6c9_24

public:
   bool has_detected_explosion() const { return detected_explosion; }
   void mark_exploded() { detected_explosion = true; }
   void mark_not_exploded() { detected_explosion = false; }
};

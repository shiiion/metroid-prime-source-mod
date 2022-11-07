#pragma once

#include "mp2/mpsdk/actor.hh"
#include "mp2/mpsdk/damage_info.hh"
#include "mp2/mpsdk/materials.hh"
#include "mp2/rstl/optional.hh"
#include "mp2/rstl/vector.hh"

enum class EProjectileAttrib {
   None = 0,
   Charged = (1 << 2),
};

enum class EWeaponType {
   None = -1,
   Power = 0,
   Dark = 1,
   Light = 2,
   Annihilator = 3,
   Missile = 6,
};

class CWeapon : public CActor {
protected:
   EProjectileAttrib projectile_attribs; // 158
   TUniqueId owner_id; // 15c
   EWeaponType weapon_type; // 160
   uint8_t cweapon_unk0[0x4]; // 164
   CMaterialFilter filter __attribute__((packed, aligned(4))); // 168
   uint8_t cweapon_unk1[0x4]; // 17c
   CDamageInfo original_damage_info; // 180
   uint8_t cweapon_unk2[0x8]; // 194
   CDamageInfo cur_damage_info; // 19c
   uint8_t cweapon_unk3[0x8]; // 1b0
   float cur_time; // 1b8

public:
   EWeaponType get_weapon_type() const { return weapon_type; }
   float get_alive_time() const { return cur_time; }
};

struct CProjectileWeapon {
   uintptr_t const* const vtable; // 0
   uint8_t weapon_desc_token[0xc]; // 4
   u32 random1; // 10
   u32 random2; // 14
   mat34 local_to_world_xf; // 18
   mat34 local_xf; // 48
   vec3 world_offset; // 78
   vec3 local_offset; // 84
   vec3 proj_offset; // 90
   vec3 cprojectileweapon_unk0; // 9c
   vec3 cprojectileweapon_unk1; // a8
   vec3 scale; // b4
   vec3 cprojectileweapon_unk2; // c0
   vec3 blur_scale; // cc
   vec3 velocity; // d8
   vec3 gravity; // e4
   uint8_t cprojectileweapon_unk3[0x40]; // f0
   float some_number; // 130
   float some_number2; // 134
   double cur_time; // 138
   uint8_t cprojectileweapon_unk4[0x50]; // 140
};

class CGameProjectile : public CWeapon {
protected:
   uint8_t cgameprojectile_unk0[0x7c]; // 1bc
   CProjectileWeapon projectile_vars; // 238
   vec3 previous_pos; // 3c8
   float projectile_extent; // 3d4
   float homing_dt; // 3d8
   uint8_t cgameprojectile_unk1[0x4]; // 3dc
   double cur_homing_time; // 3e0
   double target_homing_time; // 3e8
   TUniqueId homing_target_id; // 3f0
   TUniqueId last_resolved_obj; // 3f2
   TUniqueId cgameprojectile_unk2; // 3f4
   TUniqueId pending_damagee; // 3f6
   TUniqueId projectile_light; // 3f8
   CAssetId wpsc_id; // 3fc
   uint8_t cgameprojectile_unk3[0x10]; // 400
   bool projectile_active : 1; // 410
   // not marking more flags

public:
   void set_speed(float speed);
   void multiply_speed(float multiplier);
   bool is_projectile_active() const { return projectile_active; }
};

class CEnergyProjectile : public CGameProjectile {
protected:
   uint8_t cenergyprojectile_unk0[0x8]; // 414
   vec3 dir; // 41c
   float mag; // 428
   uint8_t cenergyprojectile_unk1[0x136]; // 42c
   bool cenergyprojectile_unk2 : 1; // 562_24
   bool dead : 1; // 562_25
   bool cenergyprojectile_unk3 : 1; // 562_26
   bool explode_now : 1; // 562_27
   bool does_cam_shake : 1; // 562_28
   bool cenergyprojectile_unk4 : 1; // 562_29
   bool cenergyprojectile_unk5 : 1; // 562_30
   bool cenergyprojectile_unk6 : 1; // 562_31
   bool cenergyprojectile_unk7 : 1; // 563_24
   bool cenergyprojectile_unk8 : 1; // 563_25
   // added this to check if we've detected an explosion yet
   bool detected_explosion : 1; // 563_26

public:
   bool has_detected_explosion() const { return detected_explosion; }
   void mark_exploded() { detected_explosion = true; }
   void mark_not_exploded() { detected_explosion = false; }
};

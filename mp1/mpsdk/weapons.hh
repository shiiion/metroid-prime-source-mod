#pragma once

#include "mp1/mpsdk/actor.hh"
#include "mp1/mpsdk/damage_info.hh"
#include "mp1/mpsdk/materials.hh"
#include "mp1/mpsdk/token.hh"
#include "mp1/rstl/optional.hh"
#include "mp1/rstl/vector.hh"

enum class EProjectileAttrib {
   None = 0,
   PartialCharge = (1 << 0),
   PlasmaProjectile = (1 << 1),
   Charged = (1 << 2),
   Ice = (1 << 3),
   Wave = (1 << 4),
   Plasma = (1 << 5),
   Phazon = (1 << 6),
   ComboShot = (1 << 7),
   Bombs = (1 << 8),
   PowerBombs = (1 << 9),
   BigProjectile = (1 << 10),
   ArmCannon = (1 << 11),
   BigStrike = (1 << 12),
   DamageFalloff = (1 << 13),
   StaticInterference = (1 << 14),
   PlayerUnFreeze = (1 << 15),
   ParticleOPTS = (1 << 16),
   KeepInCinematic = (1 << 17),
};

enum class EWeaponType {
   None = -1,
   Power = 0,
   Ice = 1,
   Wave = 2,
   Plasma = 3,
   Bomb = 4,
   PowerBomb = 5,
   Missile = 6,
   BoostBall = 7,
   Phazon = 8,
   AI = 9,
   PoisonWater = 10,
   Lava = 11,
   Heat = 12,
   Unused1 = 13,
   OrangePhazon = 14
};

class CWeapon : public CActor {
protected:
   EProjectileAttrib projectile_attribs;
   TUniqueId owner_id;
   EWeaponType weapon_type;
   CMaterialFilter filter;
   CDamageInfo original_damage_info;
   CDamageInfo cur_damage_info;
   float cur_time;
   float damage_falloff_speed;
   float damage_duration;
   float interference_duration;

public:
   EWeaponType get_weapon_type() const { return weapon_type; }
};

struct CProjectileWeapon {
   uintptr_t const* const vtable;
   TCachedToken<void*> weapon_desc;
   u32 random;
   mat34 local_to_world_xf;
   mat34 local_xf;
   vec3 world_offset;
   vec3 local_offset;
   vec3 proj_offset;
   vec3 scale;
   vec3 local_offset_2;
   vec3 velocity;
   vec3 gravity;
   u32 ambient_light_color;
   double cur_time;
   double remainder_time;
   float max_turn_rate;
   int flags;
   int lifetime;
   int child_system_update_rate;
   int cprojectileweapon_unk1;
   int cur_frame;
   int last_particle_frame;
   void* apms_gen;
   void* aps2_gen;
   void* cprojectileweapon_unk2;
   rstl::optional<TCachedToken<void*>> model;
   void* swoosh1;
   void* swoosh2;
   void* swoosh3;
   bool active : 1;
   bool APSO : 1;
   bool AP11 : 1;
   bool AP21 : 1;
   bool AS11 : 1;
   bool AS12 : 1;
   bool AS13 : 1;
   bool VMD2 : 1;
};

class CGameProjectile : public CWeapon {
protected:
   rstl::optional<TCachedToken<void*>> visor_particle;
   u16 visor_sfx;
   CProjectileWeapon projectile_vars;
   vec3 previous_pos;
   float projectile_extent;
   float homing_dt;
   double target_homing_time;
   double cur_homing_time;
   TUniqueId homing_target_id;
   TUniqueId last_resolved_obj;
   TUniqueId cgameprojectile_unk1;
   TUniqueId pending_damagee;
   TUniqueId projectile_light;
   CAssetId wpsc_id;
   rstl::vector<u8> touch_results;
   float min_homing_dist;
   bool projectile_active : 1;
   bool started_underwater : 1;
   bool water_update : 1;
   bool in_water : 1;
   bool send_projectile_collide_msg : 1;

public:
   void set_speed(float speed);
   void multiply_speed(float multiplier);
   bool is_projectile_active() const { return projectile_active; }
};

class CEnergyProjectile : public CGameProjectile {
protected:
   u32 sfx_handle;
   vec3 dir;
   float mag;
   u8 unused__cam_shake[0xd4];
   bool dead : 1;
   bool cbeamprojectile_unk1 : 1;
   bool cbeamprojectile_unk2 : 1;
   bool cam_shake_dirty : 1;
   // added this to check if we've detected an explosion yet
   bool detected_explosion : 1;
   float cur_time;

public:
   float get_alive_time() const { return cur_time; }
   bool has_detected_explosion() const { return detected_explosion; }
   void mark_exploded() { detected_explosion = true; }
   void mark_not_exploded() { detected_explosion = false; }
};
#include "freestanding.hh"
#include "mp3/mpsdk/collision.hh"
#include "mp3/mpsdk/player.hh"
#include "mp3/mpsdk/state_manager_min.hh"
#include "mp3/mpsdk/tweaks.hh"
#include "mp3/mpsdk/weapons.hh"

void rocket_jump_release() {}
void rocket_jump_suspend() {}

extern "C" {
float rocket_blast_radius = 9.f;
float rocket_velocity_multiplier = 2.f;
float rocket_jump_base_speed = 26.f;
float rocket_jump_speed_falloff_max = 0.7f;
float rocket_jump_speed_falloff_min = 0.3f;
// CHANGEME: fuck this
float rocket_jump_max_damage = 10.f;
}

void on_missile_explosion(CEnergyProjectile* projectile, float dt, CStateManager& mgr) {
   vec3 explosion_origin = projectile->get_transform().loc();
   CPlayer* player = mgr.get_player();
   vec3 player_origin = player->get_transform().loc();

   CMRay test_ray(
       explosion_origin,
       player_origin +
           vec3(0, 0, player->get_fpbounds_z() - CTweakPlayer::instance()->get_eye_offset()));
   aabox player_bbox = player->get_collision_bounds();
   player_bbox.move(player_origin);
   float ray_dist_min, ray_dist_max;
   if (ray_aabb_intersection(test_ray, player_bbox, ray_dist_min, ray_dist_max) == 2) {
      if (ray_dist_min < 0) {
         ray_dist_min = 0;
      }
      vec3 hit_point = explosion_origin + (test_ray.dir * ray_dist_min);

      const float hit_dist = (hit_point - explosion_origin).magnitude_sqr();
      const float blast_radius_sq = rocket_blast_radius * rocket_blast_radius;
      if (hit_dist > blast_radius_sq) {
         return;
      }
      const float lerp_val = 1.f - sqrt(hit_dist / blast_radius_sq);
      const float falloff =
          rocket_jump_speed_falloff_min +
          (rocket_jump_speed_falloff_max - rocket_jump_speed_falloff_min) * lerp_val;
      vec3 move_vec = test_ray.dir * (rocket_jump_base_speed * falloff);

      player->add_velocity(move_vec);
      mgr.hurt_player(rocket_jump_max_damage * lerp_val);
   }
}

extern "C" {
void hooked_energyprojectile_think(CEnergyProjectile* projectile, float dt, CStateManager& mgr) {
   const EWeaponType proj_type = projectile->get_weapon_type();
   if (is_missile(proj_type) && projectile->get_alive_time() == 0.f) {
      projectile->mark_not_exploded();
   }

   // call original think
   call_class_func<void, float, CStateManager&>(0x80072c90, projectile, dt, mgr);

   if (is_missile(proj_type) && !projectile->has_detected_explosion() &&
       !projectile->is_projectile_active()) {
      projectile->mark_exploded();
      on_missile_explosion(projectile, dt, mgr);
   }
}

// Typically this is a vec3 with a vtable before it, guessing this is some kind of Any type
struct Any {
  uintptr_t const* const vtable;
};

// NORMALLY this function passes param1 as 0, but I've added a patch to pass it the
// CProjectileWeapon being initialized
// Hack #2: Since CGameProjectile must be initialized after CWeapon, this hook point
// must have a valid entry for CWeapon::weapon_type 
u32 hooked_energyprojectile_vel_init(Any const* any, CProjectileWeapon* wpn, vec3& out_vel) {
  vec3 tmp_vel;

  const u32 orig_ret = call_vfunc<u32, u32, vec3&>(any, 3, 0, tmp_vel);
  if (is_missile(wpn->owner()->get_weapon_type())) {
    tmp_vel *= rocket_velocity_multiplier;
  }
  out_vel = tmp_vel;
  return orig_ret;
}

struct AnimState {
  struct AnimData {
    uint8_t pad[0x30];
    float elapsed;
  };
  uint8_t pad0[0xd4]; // 0 -> d4
  AnimData* data; // d4
  uint8_t pad1[0x14]; // 0xd8 -> 0xec
  u16 anim_type;
};

// Force override missile animation durations
bool hooked_rightarm_anim_active(AnimState* state, void* string_unused, float epsilon) {
  if (state->anim_type == 0x1f || state->anim_type == 0x1e) {
    return false;
  }

  return call_func<bool, AnimState*, void*, float>(0x80470e08, state, string_unused, epsilon);
}
}

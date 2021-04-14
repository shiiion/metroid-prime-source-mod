#include "freestanding.hh"
#include "mp1/mpsdk/collision.hh"
#include "mp1/mpsdk/player.hh"
#include "mp1/mpsdk/player_tweak.hh"
#include "mp1/mpsdk/state_manager_min.hh"
#include "mp1/mpsdk/weapons.hh"

void rocket_jump_release() {}
void rocket_jump_suspend() {}

extern "C" {
float rocket_blast_radius = 9.f;
float rocket_velocity_multiplier = 1.f;
float rocket_jump_base_speed = 26.f;
float rocket_jump_speed_falloff_max = 0.7f;
float rocket_jump_speed_falloff_min = 0.3f;
float rocket_jump_max_damage = 20.f;
}

void on_missile_explosion(CEnergyProjectile* projectile, float dt, CStateManager& mgr) {
   vec3 explosion_origin = projectile->get_transform().loc();
   CPlayer* player = mgr.get_player();
   vec3 player_origin = player->get_transform().loc();

   CMRay test_ray(
       explosion_origin,
       player_origin + vec3(0, 0, player->get_fpbounds_z() - CTweakPlayer::instance()->eye_offset));
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
   if (proj_type == EWeaponType::Missile && projectile->get_alive_time() == 0.f) {
      projectile->mark_not_exploded();
      projectile->multiply_speed(rocket_velocity_multiplier);
   }

   // call original think
   call_class_func<void, float, CStateManager&>(0x80214588, projectile, dt, mgr);

   if (proj_type == EWeaponType::Missile && !projectile->has_detected_explosion() &&
       !projectile->is_projectile_active()) {
      projectile->mark_exploded();
      on_missile_explosion(projectile, dt, mgr);
   }
}
}
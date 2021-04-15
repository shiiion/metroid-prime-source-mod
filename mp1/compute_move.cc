#include "freestanding.hh"
#include "mp1/mod_shared.hh"
#include "mp1/mpsdk/collision.hh"
#include "mp1/mpsdk/input.hh"
#include "mp1/mpsdk/player.hh"
#include "mp1/mpsdk/player_tweak.hh"
#include "mp1/mpsdk/state_manager_min.hh"
#include "mp1/rstl/string.hh"

constexpr float kInputEpsilon = 0.001f;

extern "C" {
float jump_restraint_table[8] = {1.f, 1.f, 1.f, 1.f, 0.3f, 1.f, 1.f, 1.f};
float accel_restraint_table[8] = {1.f, 1.f, 1.f, 1.f, 0.3f, 0.3f, 1.f, 0.3f};
// how fast can turning happen?
float airaccel_restraint_table[8] = {1.f, 1.f, 1.f, 1.f, 0.1f, 0.1f, 1.f, 1.f};
// how much speed is gained from turning?
float airmove_clamp_table[8] = {1.f, 1.f, 1.f, 1.f, 0.5f, 0.5f, 1.f, 1.f};

// Multiplier on air acceleration (primarily impacts how quickly turns can be done)
float airaccelerate_mul = 20.f;
// Multiplier on walking acceleration
float accelerate_mul = 16.5f;
// Maximum walking velocity (based on XY)
float max_walk_speed = 13.5f;
// Multiplier on friction
float friction_mul = 10.4f;
// Maximum speed gain per tick from airaccel
float airaccelerate_wishspeed_clamp = 1.2f;
// Z component of velocity on jumping
float jump_impulse = 20.f;
// Multiplier on normal player gravity
float gravity_mul = 1.f;
// Multiplier on input values, transforms input space from [0, 1] -> [0, wishspeed]
float input_wishspeed = 13.5f;
// If speed is less than this, then friction is applied based on this value (aka, the "stop speed")
float stop_speed = 6.f;
// Distance you must be underwater to get damped movement (NO GRAVITY SUIT ONLY!!)
float underwater_movement_depth = 2.f;
// Number of ticks after moving to falling state to get a double jump
int leniency_ticks = 5;
// Impulse to apply for each side dash
float side_dash_impulse = 10.f;
// Amount to reduce the height of the side dash by
float side_dash_jump_height_reduction = 0.5f;
// Height for crouching samus
float crouch_height = 1.5f;
// Speed damping for crouching samus
float crouch_max_speed_damp = 0.5f;
}

static int num_jumps = 0;
static int num_ticks_in_air = 0;
static LogToken move_stats_token = kInvalidToken;
constexpr float kNormalGrav = -35.f;
constexpr float kModdedGrav = -51.f;

static void ensure_logging_init() {
   if (move_stats_token == kInvalidToken) {
      move_stats_token = generate_debug_log_token();
   }
}

void compute_movement_release() {
   CStateManager::instance()->get_player()->set_gravity(kNormalGrav);
   move_stats_token = kInvalidToken;
}

void compute_movement_suspend() {
   CStateManager::instance()->get_player()->set_gravity(kNormalGrav);
}

void update_leniency_ticks(EPlayerMovementState move_state) {
   if (move_state != EPlayerMovementState::OnGround) {
      num_ticks_in_air++;
   } else {
      num_ticks_in_air = 0;
      num_jumps = 0;
   }
   if (num_ticks_in_air > leniency_ticks && (num_jumps == 0)) {
      num_jumps = 1;
   }
}

void compute_air_move_vel(CPlayer* player, CFinalInput* input, float dt,
                          ESurfaceRestraints restraint, vec3& vel) {
   const mat34& player_xf = player->get_transform();
   vec3 forward = player_xf.fwd(), right = player_xf.right();

   forward.z = right.z = 0;
   forward.normalize();
   right.normalize();

   float fwd_input =
       get_analog_input(ECommands::Forward, input) - get_analog_input(ECommands::Backward, input);
   float side_input =
       get_analog_input(ECommands::LookRight, input) - get_analog_input(ECommands::LookLeft, input);

   if (fabs(fwd_input) > kInputEpsilon) {
      fwd_input = sign(fwd_input) * 1.f;
   }
   if (fabs(side_input) > kInputEpsilon) {
      side_input = sign(side_input) * 1.f;
   }

   vec3 wishvel = forward * (fwd_input * input_wishspeed) + right * (side_input * input_wishspeed);
   wishvel.z = 0.f;

   const float wishspeed = wishvel.magnitude();
   const vec3 wishdir = wishspeed == 0.f ? forward : wishvel.normalized();

   const float airaccel = airaccelerate_mul * airaccel_restraint_table[static_cast<int>(restraint)];
   const float max_wishspeed =
       airaccelerate_wishspeed_clamp * airmove_clamp_table[static_cast<int>(restraint)];
   const float currentspeed = vel.dot(wishdir);

   float addspeed = min(max_wishspeed, wishspeed) - currentspeed;
   if (addspeed <= 0.f) {
      return;
   }

   const float accelspeed = min(airaccel * wishspeed * dt, addspeed);
   vel += wishdir * accelspeed;
}

void compute_friction(float dt, vec3& vel) {
   const float current_speed = vel.magnitude();
   if (current_speed < 0.1f) {
      return;
   }

   const float friction = friction_mul;
   float control = current_speed < stop_speed ? stop_speed : current_speed;
   const float drop = control * friction * dt;
   float new_speed = current_speed - drop;
   if (new_speed < 0) new_speed = 0;
   if (new_speed != current_speed) {
      new_speed /= current_speed;
      vel *= new_speed;
   }
}

void compute_walk_move_vel(CPlayer* player, CFinalInput* input, float dt,
                           ESurfaceRestraints restraint, bool crouching, vec3& vel) {
   vel.z = 0;
   // first apply friction
   compute_friction(dt, vel);
   vel.z = 0;

   const mat34& player_xf = player->get_transform();
   vec3 forward = player_xf.fwd(), right = player_xf.right();

   forward.z = right.z = 0;
   forward.normalize();
   right.normalize();

   float fwd_input =
       get_analog_input(ECommands::Forward, input) - get_analog_input(ECommands::Backward, input);
   float side_input =
       get_analog_input(ECommands::LookRight, input) - get_analog_input(ECommands::LookLeft, input);

   if (fabs(fwd_input) > kInputEpsilon) {
      fwd_input = sign(fwd_input);
   }
   if (fabs(side_input) > kInputEpsilon) {
      side_input = sign(side_input);
   }

   vec3 wishvel =
       (forward * (fwd_input * input_wishspeed)) + (right * (side_input * input_wishspeed));
   wishvel.z = 0;

   const float wishspeed = wishvel.magnitude();
   vec3 wishdir = wishvel.normalized();
   if (wishspeed == 0.f) {
      if (vel.magnitude_sqr() == 0.f) {
         wishdir = forward;
      } else {
         wishdir = vel.normalized();
      }
   }

   const float max_walk_speed_adjust = (crouching ? crouch_max_speed_damp : 1.f) * max_walk_speed;
   const float currentspeed = vel.dot(wishdir);
   const float addspeed = wishspeed - currentspeed;

   if (addspeed > 0.f) {
      // clamped wishspeed scaled by the acceleration multiplier & restraint
      // clamped again by the absolute maximum to be added
      const float accelspeed =
          min((accelerate_mul * accel_restraint_table[static_cast<int>(restraint)]) * dt *
                  max(max_walk_speed_adjust, wishspeed),
              addspeed);

      vel += wishdir * accelspeed;
   }
   vel.z = 0;

   if (vel.magnitude_sqr() > max_walk_speed_adjust * max_walk_speed_adjust) {
      vel *= (max_walk_speed_adjust / vel.magnitude());
   }
}

void compute_jump_vel(CPlayer* player, CFinalInput* input, float dt, ESurfaceRestraints restraint,
                      CStateManager& mgr, vec3& vel) {
   num_jumps++;

   float side_input =
       get_analog_input(ECommands::LookRight, input) - get_analog_input(ECommands::LookLeft, input);
   if (player->get_orbit_state() != EPlayerOrbitState::NoOrbit && fabs(side_input) > 0.05) {
      vec3 rt = player->get_transform().right() * side_input * side_dash_impulse;
      vel += rt;
      vel.z = jump_impulse * jump_restraint_table[static_cast<int>(restraint)] *
              side_dash_jump_height_reduction;
   } else {
      vel.z = jump_impulse * jump_restraint_table[static_cast<int>(restraint)];
   }
   player->set_move_state(EPlayerMovementState::Jump, mgr);
}

bool update_crouch(CPlayer* player, bool cur_crouch_button, EPlayerMovementState move_state,
                   CStateManager& mgr) {
   static bool crouch_button_state = false;
   static bool uncrouch_requested = false;
   static bool is_crouching = false;
   const float crouch_delta = 2.7f - crouch_height;

   const auto do_crouch = [crouch_delta](CPlayer* player, EPlayerMovementState move_state) {
      player->get_collision_bounds().maxes.z = crouch_height;
      player->set_fpbounds_z(crouch_height);
      if (move_state != EPlayerMovementState::OnGround) {
         player->get_transform().set_loc(player->get_transform().loc() + vec3(0, 0, crouch_delta));
      }
   };
   const auto do_uncrouch = [crouch_delta](CPlayer* player, EPlayerMovementState move_state) {
      player->get_collision_bounds().maxes.z = 2.7f;
      player->set_fpbounds_z(2.7f);
      if (move_state != EPlayerMovementState::OnGround) {
         player->get_transform().set_loc(player->get_transform().loc() - vec3(0, 0, crouch_delta));
      }
   };
   const auto collision_detect = [](CPlayer* player, CStateManager const& mgr) -> bool {
      rstl::reserved_vector<TUniqueId, 1024> near_list;
      aabox player_bbox = player->get_collision_bounds();
      player_bbox.mins += player->get_transform().loc();
      player_bbox.maxes += player->get_transform().loc();
      mgr.build_collider_list(near_list, *player, player_bbox);
      CCollidableAABox fake_bbox(CMaterialList(), player_bbox);
      constexpr CMaterialFilter filter =
          CMaterialFilter::make_include(cons_matlist(EMaterialTypes::Solid));
      return detect_collision_boolean(mgr, player->get_collision_prim(), player->get_transform(),
                                      filter, near_list);
   };

   if (crouch_button_state != cur_crouch_button) {
      if (cur_crouch_button && !uncrouch_requested) {
         do_crouch(player, move_state);
         is_crouching = true;
      } else {
         uncrouch_requested = true;
         do_uncrouch(player, move_state);
         if (collision_detect(player, mgr)) {
            if (move_state == EPlayerMovementState::OnGround) {
               do_crouch(player, move_state);
            } else {
               vec3 cast_point = player->get_transform().loc() + vec3(0, 0, crouch_delta);
               CRayCastResult result = ray_static_intersection(
                   mgr, cast_point, vec3(0, 0, -1.f), crouch_delta,
                   CMaterialFilter::make_include(cons_matlist(EMaterialTypes::Solid)));
               if (result.valid) {
                  player->get_transform().set_loc(result.point);
                  vec3 v_stop = player->get_velocity();
                  v_stop.z = 0;
                  player->set_velocity_wr(v_stop);
                  player->set_move_state(EPlayerMovementState::OnGround, mgr);
                  uncrouch_requested = false;
                  is_crouching = false;
               } else {
                  do_crouch(player, move_state);
               }
            }
         } else {
            uncrouch_requested = false;
            is_crouching = false;
         }
      }
   } else if (!cur_crouch_button && uncrouch_requested) {
      do_uncrouch(player, move_state);
      if (collision_detect(player, mgr)) {
         do_crouch(player, move_state);
      } else {
         uncrouch_requested = false;
         is_crouching = false;
      }
   }

   crouch_button_state = cur_crouch_button;
   return is_crouching;
}

extern "C" {
void hooked_computemovement(CPlayer* player, CFinalInput* input, CStateManager& mgr, float dt) {
   ensure_logging_init();

   if (player->in_morphball()) {
      player->set_gravity(kNormalGrav);
   } else {
      player->set_gravity(kModdedGrav);
   }

   const bool crouching = update_crouch(player, get_digital_input(ECommands::LookHold1, input),
                                        player->get_move_state(), mgr);

   const vec3 half_grav(0.f, 0.f, player->get_gravity() * 0.5f * gravity_mul * dt);
   const bool has_doublejump = mgr.get_player_state()->has_powerup(EItemType::SpaceJumpBoots);
   const EPlayerMovementState move_state = player->get_move_state();
   const ESurfaceRestraints restraint = player->get_surface_restraint(underwater_movement_depth);

   update_leniency_ticks(move_state);

   vec3 vel = player->get_velocity();
   vel += half_grav;

   const bool jump_pressed = get_digital_input(ECommands::JumpOrBoost, input);
   const bool jump_this_tick = get_press_input(ECommands::JumpOrBoost, input);
   if ((jump_pressed && num_jumps == 0) ||
       (jump_this_tick && move_state != EPlayerMovementState::OnGround && num_jumps == 1 &&
        has_doublejump)) {
      compute_jump_vel(player, input, dt, restraint, mgr, vel);
      player->set_velocity_wr(vel);
      return;
   }

   if (move_state != EPlayerMovementState::OnGround) {
      compute_air_move_vel(player, input, dt, restraint, vel);
   } else {
      compute_walk_move_vel(player, input, dt, restraint, crouching, vel);
   }

   vel += half_grav;
   if (move_state == EPlayerMovementState::OnGround) {
      vel.z = 0.f;
   }

   player->set_velocity_wr(vel);

   if (show_logs) {
      char move_info_str[4096];
      sprintf(move_info_str, "velocity: (%.2f %.2f %.2f)\nspeed: %.2f\nhorizontal speed: %.2f",
              restraint, vel.x, vel.y, vel.z, vel.magnitude(), vel.xy_magnitude());
      log_on_token(move_stats_token, move_info_str);
   }
}
}

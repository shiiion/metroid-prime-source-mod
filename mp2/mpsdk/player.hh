#pragma once

#include "mp2/mpsdk/input.hh"
#include "mp2/mpsdk/physics_actor.hh"
#include "mp2/mpsdk/player_state.hh"
#include "mp2/rstl/vector.hh"

enum class EPlayerMovementState { OnGround, Jump, Falling, Unk0, FallingMorphed };

enum class EPlayerMorphBallState { Unmorphed, Morphed, Morphing, Unmorphing };

// There's more of em, though for the most part they don't matter
enum class ESurfaceRestraints { Normal, Air, Unk0, Unk1, Unk2, Water, DarkWater, TheWeeds };

class CPlayer : public CPhysicsActor {
public:
   EPlayerMovementState movement_state; // 2d0
   rstl::vector<u8> ball_transition_res;
   TUniqueId attached_actor;
   float attached_actor_time;
   struct { // 2ec
      rstl::vector<u8> sources;
      float energy_drain_time;
   } energy_drain;
   float starting_jump_timeout; // 300
   float starting_jump_timer;
   float min_jump_timeout;
   float jump_camera_timer;
   u32 jump_presses; // 310
   float fall_camera_timer;
   float time_in_air;
   uint8_t cplayer_unk0[0x4];
   float time_since_jump; // 320
   float time_since_spacejump;
   float time_since_screwattack;
   vec3 last_jump_location; // 32c
   vec3 last_space_jump_location; // 338
   ESurfaceRestraints surface_restraint; // 344
   rstl::reserved_vector<float, 4> acceleration_table; // 348
   uint8_t cplayer_unk3[0x10]; // 35c
   aabox fp_bounds; // 36c
   uint8_t cplayer_unk4[0x8]; // 384
   EPlayerMorphBallState morphball_state; // 38c
   uint8_t cplayer_unk5[0xeb8]; // 390
   float water_depth; // 1248
   uint8_t cplayer_unk6[0xc8]; // 124c
   CPlayerState* player_state; // 1314
   uint8_t cplayer_unk7[0xb8]; // 1318
   rstl::reserved_vector<bool, 0x4c> player_input_mask; // 13d0

public:
   float get_gravity() const;
   void set_move_state(EPlayerMovementState state, CStateManager& mgr);
   EPlayerMovementState get_move_state() const { return movement_state; }

   ESurfaceRestraints get_surface_restraint(float underwater_move_depth) const;
   void set_fpbounds_z(float z) { fp_bounds.maxes.z = z; }
   float get_fpbounds_z() { return fp_bounds.maxes.z; }
   void* get_collision_prim() { return &collision_primitive; }
   CPlayerState const* get_player_state() const { return player_state; }
   CPlayerState* get_player_state() { return player_state; }
   float get_water_depth() const { return water_depth; }

   bool in_morphball() const;
   static void set_gravity(float g);
   
   void start_screwattack();
   void start_gravboost(CStateManager& mgr);
   void stop_gravboost(CStateManager& mgr);
   rstl::reserved_vector<bool, 0x4c>& get_input_mask() { return player_input_mask; }
   void set_saved_spacejump_z(float z) { last_space_jump_location.z = z; }
};

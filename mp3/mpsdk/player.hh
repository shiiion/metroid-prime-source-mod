#pragma once

#include "mp3/mpsdk/input.hh"
#include "mp3/mpsdk/physics_actor.hh"
#include "mp3/mpsdk/state_manager_min.hh"
#include "mp3/mpsdk/player_state.hh"

enum class EPlayerMovementState { OnGround, Jump, Falling, Unk0, FallingMorphed };

enum class EPlayerMorphBallState { Unmorphed, Morphed, Morphing, Unmorphing };

// TODO: Figure out what these are
enum class ESurfaceRestraints { Normal, Air, Unk0, Unk1, Unk2, Unk3, Unk4, Unk5 };

// This whole thing was changed, these are guesses
enum class EPlayerOrbitState {
   NoOrbit,
   OrbitObject,
   OrbitFromGrapple,
   Grapple,
};

class TCPHPrim;

class CPlayer : public CPhysicsActor {
public:
   EPlayerMovementState movement_state;    // 29c
   char cplayer_unk0[0x54];                // 2a0 -> 2f4
   vec3 last_jump_location;                // 2f4
   vec3 last_space_jump_location;          // 300
   ESurfaceRestraints surface_restraint;   // 30c
   char cplayer_unk1[0x24];                // 310 -> 334
   aabox fpbounds;                         // 334
   char cplayer_unk2[0xc];                 // 34c -> 358
   EPlayerMorphBallState morphball_state;  // 358
   char cplayer_unk3[0x14];                // 35c -> 370
   u32 orbiting_object;                    // 370
   char cplayer_unk4[0x322c];              // 374 -> 35a0
   CPlayerState* player_state;             // 35a0
   uint8_t cplayer_unk5[0x20];             // 35a4 -> 35c4
   void* player_input_mask;                // 35c4
   uint8_t cplayer_unk6[0x4f0];            // 35c8 -> 3ab8
   // Not sure why but prime 3 switched to using this guy primarily instead
   void* real_collision;               // 3ab8

public:
   float get_fpbounds_z() const { return fpbounds.maxes.z; }
   void set_fpbounds_z(float z) { fpbounds.maxes.z = z; }
   float get_gravity() const;
   void set_move_state(EPlayerMovementState state, CStateManager& mgr);
   EPlayerMovementState get_move_state() const { return movement_state; }
   ESurfaceRestraints get_surface_restraint() { return surface_restraint; }
   bool is_orbiting() { return orbiting_object != 0; }
   u32 get_orbit_mode() { return orbiting_object; }
   bool in_morphball() const;
   static void set_gravity(float g);
   CPlayerState* get_player_state() { return player_state; }

   void start_screwattack();
   void* get_input_mask() { return &player_input_mask; }
   void set_saved_spacejump_z(float z) { last_space_jump_location.z = z; }
   void* get_active_prim() { return real_collision; }
   void* swap_active_prim(void* repl) {
      void* tmp = real_collision;
      real_collision = repl;
      return tmp;
   }
};

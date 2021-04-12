#pragma once

#include "mp1/mpsdk/physics_actor.hh"
#include "mp1/mpsdk/player_state.hh"
#include "mp1/rstl/vector.hh"

enum class EPlayerScanState { NotScanning, Scanning, ScanComplete };

enum class EPlayerOrbitType { Close, Far, Default };

enum class EPlayerOrbitState {
   NoOrbit,
   OrbitObject,
   OrbitPoint,
   OrbitCarcass,
   ForcedOrbitObject,  // For CMetroidBeta attack
   Grapple
};

enum class EPlayerOrbitRequest {
   StopOrbit,
   Respawn,
   EnterMorphBall,
   Default,
   Four,
   Five,
   InvalidateTarget,
   BadVerticalAngle,
   ActivateOrbitSource,
   ProjectileCollide,
   Freeze,
   DamageOnGrapple,
   LostGrappleLineOfSight
};

enum class EPlayerZoneInfo { Targeting, Scan };

enum class EPlayerZoneType { Always = -1, Box = 0, Ellipse };

enum class EPlayerMovementState { OnGround, Jump, ApplyJump, Falling, FallingMorphed };

enum class EPlayerMorphBallState { Unmorphed, Morphed, Morphing, Unmorphing };

enum class EPlayerCameraState { FirstPerson, Ball, Two, Transitioning, Spawned };

enum class ESurfaceRestraints { Normal, Air, Ice, Organic, Water, Lava, Phazon, Shrubbery };

enum class EFootstepSfx { None, Left, Right };

enum class EGrappleState { None, Firing, Pull, Swinging, JumpOff };

enum class EGunHolsterState { Holstered, Drawing, Drawn, Holstering };

class CPlayer : public CPhysicsActor {
protected:
   EPlayerMovementState movement_state;
   // Correct vector types only if needed
   rstl::vector<u8> ball_transition_res;
   TUniqueId attached_actor;
   float attached_actor_time;
   struct {
      rstl::vector<u8> sources;
      float energy_drain_time;
   } energy_drain;
   float starting_jump_timeout;
   float starting_jump_timer;
   float min_jump_timeout;
   float jump_camera_timer;
   u32 jump_presses;
   float fall_camera_timer;
   float cplayer_unk1;
   bool cancel_camera_pitch;
   float time_since_jump;
   ESurfaceRestraints surface_restraint;
   u32 out_of_water_ticks;
   rstl::reserved_vector<float, 6> acceleration_table;
   u32 cur_acceleration;
   float acceleration_change_timer;
   aabox fp_bounds;
   float ball_trans_height;
   EPlayerCameraState camera_state;
   EPlayerMorphBallState morphball_state;
   EPlayerMorphBallState spawned_morphball_state;
   float falling_time;
   EPlayerOrbitState orbit_state;
   EPlayerOrbitType orbit_type;
   EPlayerOrbitRequest orbit_request;
   TUniqueId orbit_target_id;
   vec3 orbit_point;
   vec3 orbit_vector;
   float orbit_mode_timer;
   EPlayerZoneInfo orbit_zone_mode;
   EPlayerZoneType orbit_zone_type;
   u32 cplayer_unk2;
   TUniqueId orbit_next_target_id;
   float cplayer_unk3;
   rstl::vector<TUniqueId> nearby_orbit_objects;
   rstl::vector<TUniqueId> on_screen_orbit_objects;
   rstl::vector<TUniqueId> off_screen_orbit_objects;
   bool orbit_lock_established;
   float orbit_prevention_timer;
   bool sideways_dashing;
   float strafe_input_at_dash;
   float dash_timer;
   float dash_button_hold_time;
   bool done_sideways_dashing;
   u32 orbit_source;
   bool orbiting_enemy;
   float dash_speed_multiplier;
   bool no_strafe_dash_blend;
   float dash_duration;
   float strafe_dash_blend_duration;
   EPlayerScanState scan_state;
   float scanning_time;
   float cur_scan_time;
   TUniqueId scannin_object;
   EGrappleState grapple_state;
   float grapple_swing_timer;
   vec3 grapple_swing_axis;
   float cplayer_unk4;
   float cplayer_unk5;
   float cplayer_unk6;
   float grapple_jump_timeout;
   bool in_free_look;
   bool look_Button_held;
   bool look_analog_held;
   float cur_free_look_centered_time;
   float free_look_yaw_angle;
   float horiz_free_look_ang_vel;
   float free_look_pitch_angle;
   float vert_free_look_angle_vel;
   TUniqueId aim_target;
   vec3 target_aim_position;
   u8 cplayer_reservedaverage1[0x7c];
   vec3 assisted_target_aim;
   float im_target_timer;
   void* player_gun;
   float gun_alpha;
   EGunHolsterState gun_holster_state;
   float gun_holster_rem_time;
   void* failsafe_test;
   u8 cplayer_reservedaverage2[0x54];
   float move_speed;
   float flat_move_speed;
   vec3 look_dir;
   vec3 move_dir;
   vec3 leave_morph_dir;
   vec3 last_pos_for_dir_calc;
   vec3 gun_dir;
   float time_moving;
   vec3 control_dir;
   vec3 control_dir_flat;
   bool was_damaged;
   float damage_amount;
   float prev_damage_amount;
   vec3 damage_location;
   float immune_timer;
   float morph_time;
   float morph_duration;
   u32 cplayer_unk7;
   u32 cplayer_unk8;
   int ball_transition_anim;
   float alpha;
   float transition_vel;
   bool leave_morphball_allowed;
   u8 cplayer_reservedaverage3[0xc4];
   u8 cplayer_reservedaverage4[0xc4];
   u8 cplayer_reservedaverage5[0x14];
   rstl::vector<void*> transition_models;
   float static_timer;
   float static_out_speed;
   float static_in_speed;
   float visor_static_alpha;
   float frozen_timeout;
   s32 ice_break_jumps;
   float frozen_timeout_bias;
   s32 additional_ice_break_jumps;
   bool controls_frozen;
   float controls_frozen_timeout;
   void* player_morphball;
   void* camera_bob;
   u32 damage_loop_sfx;
   float samus_voice_timeout;
   u32 dash_sfx;
   u32 samus_voice_sfx;
   int samus_voice_priority;
   float damage_sfx_timer;
   u16 damage_loop_sfx_id;
   float footstep_sfx_timer;
   EFootstepSfx footstep_sfx_sel;
   vec3 last_velocity;
   struct {
      float cur_target_alpha;
      float cur_alpha_in_dur;
      float cur_alpha_out_dur;
      CAssetId tex;
      float next_target_alhpa;
      float next_alpha_in_dur;
      float next_alpha_out_dur;
      CAssetId txtr;
      float alhpa;
      float delay_timer;
      bool affects_thermal;
   } visor_steam;
   EPlayerSuit transition_suit;
   u8 cplayer_unk9[0x8];
   vec3 beam_scale;
   bool cplayer_unk10;
   u32 cplayer_unk11;
   EBeamId player_beam;
   void* ball_transition_beam_model;
   mat34 gun_world_xf;
   float transition_filter_timer;
   float distance_underwater;
   bool in_lava;
   TUniqueId riding_platform;
   TUniqueId player_Hint;
   u32 player_hint_priority;
   struct PlayerHint {
      u32 prio;
      TUniqueId id;
   };
   rstl::reserved_vector<PlayerHint, 32> player_hints;
   rstl::reserved_vector<TUniqueId, 32> player_hints_to_remove;
   rstl::reserved_vector<TUniqueId, 32> player_hints_to_add;
   bool visor_change_requested : 1;
   bool show_crosshairs : 1;
   bool cplayer_unk12 : 1;
   bool can_enter_morph_ball : 1;
   bool can_leave_morph_ball : 1;
   bool spider_ball_control_XY : 1;
   bool control_dir_override : 1;
   bool in_water_movement : 1;
   bool cplayer_unk13 : 1;
   bool splash_updated : 1;
   bool cplayer_unk14 : 1;
   bool cam_submerged : 1;
   bool sliding_on_wall : 1;
   bool hit_wall : 1;
   bool select_fluid_ball_sound : 1;
   bool step_camera_z_bias_dirty : 1;
   bool extend_target_distance : 1;
   bool interpolating_control_dir : 1;
   bool out_of_ball_look_at_hint : 1;
   bool aiming_at_projectile : 1;
   bool aligning_grapple_swing_turn : 1;
   bool disable_input : 1;
   bool new_scan_scanning : 1;
   bool override_radar_radius : 1;
   bool no_damage_loop_sfx : 1;
   bool out_of_ball_look_at_hint_actor : 1;
   float eye_z_bias;
   float ste_camera_z_bias;
   u32 bomb_jump_count;
   s32 bomb_jump_delay_frames;
   vec3 control_dir_override_dir;
   rstl::reserved_vector<TUniqueId, 5> orbit_disable_list;
   float death_time;
   float control_Dir_interp_time;
   float control_dir_interp_dur;
   TUniqueId death_power_bomb;
   float pre_think_dt;
   CAssetId steam_texture_id;
   CAssetId ice_texture_id;
   u32 env_dmg_counter;
   float env_dmg_camera_shake_timer;
   float phazon_damage_lag;
   float threat_override;
   float radar_xy_radius_override;
   float radar_z_radius_override;
   float attached_actor_struggle;
   int damage_loop_sfx_delay_ticks;
   float samus_exhausted_voice_timer;

public:
   float get_gravity() const { return call_class_func<float>(0x8028835c, this); }

   void set_move_state(EPlayerMovementState state, CStateManager& mgr) {
      call_class_func<void, EPlayerMovementState, CStateManager&>(0x802863ec, this, state, mgr);
   }
   EPlayerMovementState get_move_state() const { return movement_state; }
   EPlayerOrbitState get_orbit_state() const { return orbit_state; }

   ESurfaceRestraints get_surface_restraint(float underwater_move_depth) const;
   bool in_morphball() const;
   static void set_gravity(float g);
};
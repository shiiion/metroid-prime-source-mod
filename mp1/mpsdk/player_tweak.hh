#pragma once

#include "freestanding.hh"

struct CTweakPlayer {
private:
   uintptr_t const* const vtable;

public:
   NO_INSTANTIATE(CTweakPlayer);
   static CTweakPlayer* instance() { return reinterpret_cast<CTweakPlayer*>(0x8045c208); }

   float max_translational_acceleration[8];
   float max_rotational_acceleration[8];
   float translation_friction[8];
   float rotation_friction[8];
   float rotation_max_speed[8];
   float translation_max_speed[8];
   float normal_grav_accel;
   float fluid_grav_accel;
   float vertical_jump_accel;
   float horizontal_jump_accel;
   float vertical_double_jump_accel;
   float horizontal_double_jump_accel;
   float water_jump_factor;
   float water_ball_jump_factor;
   float lava_jump_factor;
   float lava_ball_jump_factor;
   float phazon_jump_factor;
   float phazon_ball_jump_factor;
   float allowed_jump_time;
   float allowed_double_jump_time;
   float min_double_jump_window;
   float max_double_jump_window;
   float unk1;
   float min_jump_time;
   float min_double_jump_time;
   float allowed_ledge_time;
   float double_jump_impulse;
   float backwards_force_multiplier;
   float bomb_jump_radius;
   float bomb_jump_height;
   float eye_offset;
   float turn_speed_multiplier;
   float free_look_turn_speed_multiplier;
   float horizontal_free_look_angle_vel;
   float vertical_free_look_angle_vel;
   float free_look_speed;
   float free_look_snap_speed;
   float unk2;
   float free_look_centered_threshold_angle;
   float free_look_centered_time;
   float free_look_dampen_factor;
   float left_div;
   float right_div;
   float orbit_min_distance[3];
   float orbit_normal_distance[3];
   float orbit_max_distance[3];
   float unk3;
   float orbit_mode_timer;
   float orbit_camera_speed;
   float orbit_upper_angle;
   float orbit_lower_angle;
   float orbit_horiz_angle;
   float unk4;
   float unk5;
   float orbit_max_target_distance;
   float orbit_max_lock_distance;
   float orbit_distance_threshold;
   u32 orbit_screen_box_half_extent_x[2];
   u32 orbit_screen_box_half_extent_y[2];
   u32 orbit_screen_box_center_x[2];
   u32 orbit_screen_box_center_y[2];
   u32 orbit_zone_ideal_x[2];
   u32 orbit_zone_ideal_y[2];
   float orbit_near_x;
   float orbit_near_z;
   float unk6;
   float unk7;
   float orbit_fixed_offset_z_diff;
   float orbit_z_range;
   float unk8;
   float unk9;
   float unk10;
   float orbit_prevention_time;
   bool dash_enabled : 1;
   bool dash_on_button_release : 1;
   float dash_button_hold_cancel_time;
   float dash_strafe_input_threshold;
   float sideways_double_jump_impulse;
   float sideways_vertical_double_jump_accel;
   float sideways_horizontal_double_jump_accel;
   float scanning_range;
   bool scan_retention : 1;
   bool scan_freezes_game : 1;
   bool orbit_while_scanning : 1;
   float scan_max_target_distance;
   float scan_max_lock_distance;
   bool freelook_turns_player : 1;
   bool unk11 : 1;
   bool unk12 : 1;
   bool move_during_free_look : 1;
   bool hold_buttons_for_free_look : 1;
   bool two_buttons_for_free_look : 1;
   bool unk13 : 1;
   bool unk14 : 1;
   bool unk15 : 1;
   bool aim_when_orbiting_point : 1;
   bool stay_in_free_look_while_firing : 1;
   bool unk16 : 1;
   bool unk17 : 1;
   bool orbit_fixed_offset : 1;
   bool gun_button_toggles_holster : 1;
   bool gun_not_firing_holsters_gun : 1;
   bool falling_double_jump : 1;
   bool impulse_double_jump : 1;
   bool firing_cancels_camera_pitch : 1;
   bool assisted_aiming_ignore_horizontal : 1;
   bool assisted_aiming_ignore_vertical : 1;
   float unk18;
   float unk19;
   float aim_max_distance;
   float unk20;
   float unk21;
   float unk22;
   float unk23;
   float unk24;
   float aim_threshold_distance;
   float unk25;
   float unk26;
   float aim_box_width;
   float aim_box_height;
   float aim_target_timer;
   float aim_assist_horizontal_angle;
   float aim_assist_vertical_angle;
   float player_height;
   float player_x_y_half_extent;
   float step_up_height;
   float step_down_height;
   float player_ball_half_extent;
   float first_person_camera_speed;
   float unk27;
   float jump_camera_pitch_down_start;
   float jump_camera_pitch_down_full;
   float jump_camera_pitch_down_angle;
   float fall_camera_pitch_down_start;
   float fall_camera_pitch_down_full;
   float fall_camera_pitch_down_angle;
   float orbit_distance_max;
   float grapple_swing_length;
   float grapple_swing_period;
   float grapple_pull_speed_min;
   float grapple_camera_speed;
   float max_grapple_locked_turn_align_distance;
   float grapple_pull_speed_proportion;
   float grapple_pull_speed_max;
   float grapple_look_center_speed;
   float max_grapple_turn_speed;
   float grapple_jump_force;
   float grapple_release_time;
   u32 grapple_jump_mode;
   bool orbit_release_breaks_grapple;
   bool invert_grapple_turn;
   float grapple_beam_speed;
   float grapple_beam_x_wave_amplitude;
   float grapple_beam_z_wave_amplitude;
   float grapple_beam_angle_phase_delta;
   float unk28;
   float unk29;
   float unk30;
   bool unk31;
   float frozen_timeout;
   u32 ice_break_jump_count;
   float varia_damage_reduction;
   float gravity_damage_reduction;
   float phazon_damage_reduction;
};
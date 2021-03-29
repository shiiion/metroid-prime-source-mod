#pragma once

#include "freestanding.hh"
#include "mp1/rstl/string.hh"

#define sprintf(str, fmt, ...) \
   ((int (*)(char*, const char*, ...))0x8038dcdc)((str), (fmt), __VA_ARGS__)

using LogToken = s32;
constexpr LogToken kInvalidToken = -1;
constexpr float kNormalDt = 1.f / 60.f;
constexpr double kNormalDtLong = 1.0 / 60.0;

LogToken generate_debug_log_token();
void log_on_token(LogToken tok, rstl::string const& str);
rstl::string get_log_string();

// Release for each source file
void cmfgame_hooks_release();
void compute_movement_release();
void rocket_jump_release();
void partfx_timescale_release();

// Suspend for each source file
void cmfgame_hooks_suspend();
void compute_movement_suspend();
void rocket_jump_suspend();
void partfx_timescale_suspend();

// Good mod-global vars
extern bool dt_just_changed;

extern "C" {
// CMFGame Hooks
extern float game_timescale;
extern bool show_logs;

// Compute Move
extern float jump_restraint_table[8];
extern float accel_restraint_table[8];
extern float airaccel_restraint_table[8];
extern float airmove_clamp_table[8];
extern float airaccelerate_mul;
extern float accelerate_mul;
extern float max_walk_speed;
extern float friction_mul;
extern float airaccelerate_wishspeed_clamp;
extern float jump_impulse;
extern float gravity_mul;
extern float input_wishspeed;
extern float stop_speed;
extern float underwater_movement_depth;
extern int leniency_ticks;

// Rocket Jump
extern float rocket_blast_radius;
extern float rocket_velocity_multiplier;
extern float rocket_jump_base_speed;
extern float rocket_jump_speed_falloff_max;
extern float rocket_jump_speed_falloff_min;
extern float rocket_jump_max_damage;

// Mod Shared
extern char debug_output[4096];
}

// Cleanup stuffs
extern "C" {
extern int shutdown_signal;
void release_mod();
}
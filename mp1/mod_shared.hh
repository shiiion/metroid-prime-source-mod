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

// Good mod-global vars
extern bool dt_just_changed;

extern "C" {
extern float game_timescale;
}
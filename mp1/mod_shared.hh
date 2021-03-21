#pragma once

#include "freestanding.hh"
#include "mp1/rstl/string.hh"

#define sprintf(str, fmt, ...) \
   ((int (*)(char*, const char*, ...))0x8038dcdc)((str), (fmt), __VA_ARGS__)

using LogToken = s32;
constexpr LogToken kInvalidToken = -1;

LogToken generate_debug_log_token();
void log_on_token(LogToken tok, rstl::string const& str);
rstl::string get_log_string();

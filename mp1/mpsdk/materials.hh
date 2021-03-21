#pragma once

#include "freestanding.hh"

using CMaterialList = u64;

enum FilterType { Always, Include, Exclude, IncludeExclude };

struct CMaterialFilter {
   CMaterialList include;
   CMaterialList exclude;
   u32 filter_type;
};
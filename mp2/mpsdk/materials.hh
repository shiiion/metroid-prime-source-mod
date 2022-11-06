#pragma once

#include <type_traits>

#include "freestanding.hh"

enum class EMaterialTypes {
   Solid = 0x3b,
};

using CMaterialList = u64;

template <typename... Ts>
constexpr CMaterialList cons_matlist(Ts... types) {
   static_assert((std::is_same_v<Ts, EMaterialTypes> && ...),
                 "cons_matlist only accepts EMaterialTypes");
   return CMaterialList{0} | ((CMaterialList{1} << static_cast<uint32_t>(types)) | ...);
}

enum class FilterType { Always, Include, Exclude, IncludeExclude };

struct CMaterialFilter {
   CMaterialList include = 0;
   CMaterialList exclude = 0;
   FilterType filter_type = FilterType::IncludeExclude;

   constexpr CMaterialFilter(CMaterialList const& include, CMaterialList const& exclude,
                             FilterType filter_type)
       : include(include), exclude(exclude), filter_type(filter_type) {}

   static constexpr CMaterialFilter make_include_exclude(CMaterialList const& include,
                                                         CMaterialList const& exclude) {
      return CMaterialFilter(include, exclude, FilterType::IncludeExclude);
   }

   static constexpr CMaterialFilter make_include(CMaterialList const& include) {
      return CMaterialFilter(include, CMaterialList(), FilterType::Include);
   }

   static constexpr CMaterialFilter make_exclude(CMaterialList const& exclude) {
      return CMaterialFilter(CMaterialList{0x00000000ffffffff}, exclude, FilterType::Exclude);
   }
} __attribute__((packed, aligned(4)));

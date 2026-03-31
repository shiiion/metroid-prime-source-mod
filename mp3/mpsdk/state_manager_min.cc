#include "mp3/mpsdk/state_manager_min.hh"

#include "mp3/mpsdk/damage_info.hh"
#include "mp3/mpsdk/materials.hh"
#include "mp3/mpsdk/player.hh"
#include "util/r_math.hh"

constexpr u32 kInvalidUniqueId = 0xffffffff;

void CStateManager::hurt_player(float amount) {
   const CDamageInfo dinfo(amount, 0);
   call_class_func<void, u32, u32, u32, CDamageInfo const&,
                   CMaterialFilter const&, vec3 const&>(
      0x80274acc, this, kInvalidUniqueId, get_player()->get_unique_id(), kInvalidUniqueId, dinfo,
      CMaterialFilter::make_include_exclude(cons_matlist(EMaterialTypes::Solid), CMaterialList()),
      vec3());
}

void CStateManager::build_collider_list(rstl::reserved_vector<u32, 2048>& collider_out,
                                        CActor const& obj, aabox const& bbox) const {
   call_class_func<void, rstl::reserved_vector<u32, 2048>&, CActor const&,
                   aabox const&>(0x8027a44c, cdata, collider_out, obj, bbox);
}

#include "mp2/mpsdk/state_manager_min.hh"

#include "mp2/mpsdk/damage_info.hh"
#include "mp2/mpsdk/materials.hh"
#include "mp2/mpsdk/player.hh"
#include "util/r_math.hh"

CPlayerState* CStateManager::get_player_state() const {
   if (player_list.size() > 0 && player_list[0]) {
      return player_list[0]->get_player_state();
   }
   return nullptr;
}

CEntity* CStateManager::object_by_id(TUniqueId id) const {
   // There's two exact duplicate functions that do this, I'm not losing it
   return call_class_func<CEntity*, TUniqueId>(0x80041968, this, id);
}

void CStateManager::hurt_player(float amount) {
   const CDamageInfo dinfo(amount, 0);
   call_class_func<void, TUniqueId, TUniqueId, TUniqueId, CDamageInfo const&,
                   CMaterialFilter const&, vec3 const&>(
      0x8003e25c, this, kInvalidUniqueId, get_player()->get_unique_id(), kInvalidUniqueId, dinfo,
      CMaterialFilter::make_include_exclude(cons_matlist(EMaterialTypes::Solid), CMaterialList()),
      vec3());
}

void CStateManager::build_collider_list(rstl::reserved_vector<TUniqueId, 1024>& collider_out,
                                        CActor const& obj, aabox const& bbox) const {
   return call_class_func<void, rstl::reserved_vector<TUniqueId, 1024>&, CActor const&,
                          aabox const&>(0x80041ac0, this, collider_out, obj, bbox);
}

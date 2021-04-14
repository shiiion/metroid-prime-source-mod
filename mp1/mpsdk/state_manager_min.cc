#include "mp1/mpsdk/state_manager_min.hh"

#include "mp1/mpsdk/damage_info.hh"
#include "mp1/mpsdk/materials.hh"
#include "mp1/mpsdk/player.hh"
#include "mp1/mpsdk/r_math.hh"

CPlayerState* CStateManager::get_player_state() const {
   return player_state == nullptr ? nullptr : *player_state;
}

CEntity* CStateManager::object_by_id(TUniqueId id) const {
   return call_class_func<CEntity*, TUniqueId>(0x8004C574, this, id);
}

bool CStateManager::hurt_player(float amount) {
   const CDamageInfo dinfo(amount, 0);
   return call_class_func<bool, TUniqueId, TUniqueId, TUniqueId, CDamageInfo const&,
                          CMaterialFilter const&, vec3 const&>(
       0x8004a0a0, this, kInvalidUniqueId, player->get_unique_id(), kInvalidUniqueId, dinfo,
       CMaterialFilter::make_include_exclude(cons_matlist(EMaterialTypes::Solid), CMaterialList()),
       vec3());
}

void CStateManager::build_collider_list(rstl::reserved_vector<TUniqueId, 1024>& collider_out,
                                        CActor const& obj, aabox const& bbox) const {
   return call_class_func<void, rstl::reserved_vector<TUniqueId, 1024>&, CActor const&,
                          aabox const&>(0x8004c6fc, this, collider_out, obj, bbox);
}
#include "mp1/mpsdk/state_manager_min.hh"

#include "mp1/mpsdk/materials.hh"
#include "mp1/mpsdk/player.hh"
#include "mp1/mpsdk/r_math.hh"
#include "mp1/mpsdk/damage_info.hh"

bool CStateManager::hurt_player(float amount) {
   const CDamageInfo dinfo(amount, 0);
   CMaterialFilter filter{0x80000, 0, 3};
   return call_class_func<bool, TUniqueId, TUniqueId, TUniqueId, CDamageInfo const&,
                          CMaterialFilter const&, vec3 const&>(
       0x8004a0a0, this, kInvalidUniqueId, player->get_unique_id(), kInvalidUniqueId, dinfo, filter,
       vec3());
}
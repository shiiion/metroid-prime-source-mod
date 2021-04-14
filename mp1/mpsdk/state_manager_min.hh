#pragma once

#include "mp1/mpsdk/r_math.hh"
#include "mp1/mpsdk/retro_types.hh"
#include "mp1/rstl/vector.hh"
#include "util/func_caller.hh"

class CEntity;
class CActor;
class CPlayer;
class CPlayerState;

// Reduced to the bare necessities
class CStateManager {
   s16 next_free_index;
   u8 padding__1[0x6];
   u16 id_arr[1024];
   u8 unused__obj_lists[0x44];
   CPlayer* player;
   void* world;
   rstl::vector<TUniqueId> object_graveyard;
   u8 unused__members1[0x54];
   // Marked as shared_ptr, correct me later!
   CPlayerState** player_state;
   u8 unused__members2[0x6dc];

public:
   NO_INSTANTIATE(CStateManager);

   static CStateManager* instance() { return reinterpret_cast<CStateManager*>(0x8045a1a8); }
   CPlayer* get_player() const { return player; }
   CPlayerState* get_player_state() const;
   CEntity* object_by_id(TUniqueId id) const;
   bool hurt_player(float amount);
   void build_collider_list(rstl::reserved_vector<TUniqueId, 1024>& collider_out, CActor const& obj,
                            aabox const& bbox) const;
};
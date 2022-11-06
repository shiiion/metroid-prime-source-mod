#pragma once

#include "mp2/mpsdk/retro_types.hh"
#include "mp2/rstl/vector.hh"
#include "util/func_caller.hh"
#include "util/r_math.hh"

class CEntity;
class CActor;
class CPlayer;
class CPlayerState;

struct ObjectListEntry {
   bool present;
   void* object_list;
};

// Reduced to the bare necessities
class CStateManager {
   s16 next_free_index; // 0
   rstl::reserved_vector<u16, 0x400> id_list; // 4
   rstl::reserved_vector<ObjectListEntry, 8> object_lists; // 808
   uint8_t cstatemanager_unk0[0xcac];
   rstl::reserved_vector<CPlayer*, 4> player_list; // 14f8
   // More after, ignored

public:
   NO_INSTANTIATE(CStateManager);

   static CStateManager* instance() { return reinterpret_cast<CStateManager*>(0x8045a1a8); }
   size_t get_num_players() const { return player_list.size(); }
   CPlayer* get_player() const { return player_list[0]; }
   CPlayer* get_player_by_num(int num) { return player_list[num]; }
   CPlayerState* get_player_state() const; // Leaving this here for simplicity, but it's grabbed from player 1
   CEntity* object_by_id(TUniqueId id) const;
   void hurt_player(float amount);
   void build_collider_list(rstl::reserved_vector<TUniqueId, 1024>& collider_out, CActor const& obj,
                            aabox const& bbox) const;
};

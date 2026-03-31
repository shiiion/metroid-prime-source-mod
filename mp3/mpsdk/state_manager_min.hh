#pragma once

#include "mp3/rstl/vector.hh"
#include "util/func_caller.hh"
#include "util/r_math.hh"

class CActor;
class CPlayer;

// Prime 3 passes the state manager around in another object (which is probably the actual state manager)
// but this object has the closest analogues to older games
class CStateManager {
public:
   struct ObjectData {
      uint8_t unk0[0x2184]; // 0 -> 2184
      CPlayer* player; // 2184
   };
   struct CollisionData {};

   uint8_t cstatemanager_unk0[0x28];
   ObjectData* odata;
   CollisionData* cdata;

   NO_INSTANTIATE(CStateManager);

   static CStateManager* instance() { return reinterpret_cast<CStateManager*>(0x805c4f70); }
   CPlayer* get_player() const { return odata->player; }
   void hurt_player(float amount);
   void build_collider_list(rstl::reserved_vector<u32, 2048>& collider_out,
                            CActor const& obj, aabox const& bbox) const;
};

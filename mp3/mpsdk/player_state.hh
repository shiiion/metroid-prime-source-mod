#pragma once

#include "freestanding.hh"
#include "mp3/rstl/vector.hh"

enum class EItemType : s32 {
   Invalid = -1,
   ScrewAttack = 16,
};

class CPlayerState {
public:
   struct CPowerUp {
      u32 amount;
      u32 capacity;
      uint8_t cpowerup_unk0[0x4];
   };
   uint8_t cplayerstate_unk0[0x50];
   rstl::reserved_vector<CPowerUp, 0x46> powerups;

public:
   bool has_powerup(EItemType power) const {
      return powerups[static_cast<s32>(power)].capacity != 0;
   }
};

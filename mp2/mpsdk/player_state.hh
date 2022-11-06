#pragma once

#include "freestanding.hh"
#include "mp2/mpsdk/retro_types.hh"
#include "mp2/rstl/vector.hh"

enum class EBeamId : s32 { Invalid = -1, Power, Ice, Wave, Plasma, Phazon, Phazon2 = 27 };

enum class EPlayerSuit : s32 {
   Invalid = -1,
   Varia,
   Dark,
   Light,
};

enum class EPlayerVisor : u32 { Combat, Echo, Scan, Dark, Max };

enum class EItemType : s32 {
   Invalid = -1,
   PowerBeam = 0,
   DarkBeam = 1,
   LightBeam = 2,
   AnnihilatorBeam = 3,
   //4,
   //5,
   //6,
   //7,
   CombatVisor = 8,
   ScanVisor = 9,
   DarkVisor = 10,
   EchoVisor = 11,
   //12,
   //13,
   //14,
   MorphBall = 15,
   BoostBall = 16,
   //17,
   MorphBallBombs = 18,
   //19,
   //20,
   //21,
   ChargeBeam = 22,
   //23,
   SpaceJump = 24,
   GravityBoost = 25,
   ScrewAttack = 27,
   // Bunch of unknowns
   Missiles = 44,
   BeamAmmo = 45,
};

struct CHealthInfo {
   float max_health;
   float health;
   float knockback_resistance;
};

class CPlayerState {
public:
   struct CPowerUp {
      u32 amount;
      u32 capacity;
      uint8_t cpowerup_unk0[0x4];
   };
   uint8_t cplayerstate_unk0[0x4];

   union {
      struct {
         bool alive : 1;
      };
      uint8_t cplayerstate_unk1[0x8];
   };
   EBeamId current_beam;
   CHealthInfo health;
   uint8_t cplayerstate_unk2[0x14];
   EPlayerVisor current_visor;
   EPlayerVisor transitioning_visor;
   uint8_t cplayerstate_unk3[0x10];
   float charge_factor;
   uint8_t cplayerstate_unk4[0x4];
   float visor_transition_factor;
   EPlayerSuit current_suit;
   rstl::reserved_vector<CPowerUp, 0x6d> powerups;

public:
   bool has_powerup(EItemType power) const {
      return powerups[static_cast<s32>(power)].capacity != 0;
   }
   EPlayerSuit get_suit() const { return current_suit; }
};

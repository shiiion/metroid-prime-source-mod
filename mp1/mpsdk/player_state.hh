#pragma once

#include "freestanding.hh"
#include "mp1/mpsdk/retro_types.hh"
#include "mp1/rstl/vector.hh"

enum class EBeamId : s32 { Invalid = -1, Power, Ice, Wave, Plasma, Phazon, Phazon2 = 27 };

enum class EPlayerSuit : s32 {
   Invalid = -1,
   Power,
   Gravity,
   Varia,
   Phazon,
   FusionPower,
   FusionGravity,
   FusionVaria,
   FusionPhazon
};

enum class EPlayerVisor : u32 { Combat, XRay, Scan, Thermal, Max };

enum class EItemType : s32 {
   Invalid = -1,
   PowerBeam = 0,
   IceBeam = 1,
   WaveBeam = 2,
   PlasmaBeam = 3,
   Missiles = 4,
   ScanVisor = 5,
   MorphBallBombs = 6,
   PowerBombs = 7,
   Flamethrower = 8,
   ThermalVisor = 9,
   ChargeBeam = 10,
   SuperMissile = 11,
   GrappleBeam = 12,
   XRayVisor = 13,
   IceSpreader = 14,
   SpaceJumpBoots = 15,
   MorphBall = 16,
   CombatVisor = 17,
   BoostBall = 18,
   SpiderBall = 19,
   PowerSuit = 20,
   GravitySuit = 21,
   VariaSuit = 22,
   PhazonSuit = 23,
   EnergyTanks = 24,
   UnknownItem1 = 25,
   HealthRefill = 26,
   UnknownItem2 = 27,
   Wavebuster = 28,
   Truth = 29,
   Strength = 30,
   Elder = 31,
   Wild = 32,
   Lifegiver = 33,
   Warrior = 34,
   Chozo = 35,
   Nature = 36,
   Sun = 37,
   World = 38,
   Spirit = 39,
   Newborn = 40,
   Max
};

struct CHealthInfo {
   float health;
   float knockback_resistance;
};

class CPlayerState {
   public:
   struct CPowerUp {
      u32 amount;
      u32 capacity;
   };

   bool alive : 1;
   bool firing_combo_beam : 1;
   bool fusion : 1;
   u32 enabled_items;
   EBeamId current_beam;
   CHealthInfo health;
   EPlayerVisor current_visor;
   EPlayerVisor transitioning_visor;
   float visor_transition_factor;
   EPlayerSuit current_suit;
   rstl::reserved_vector<CPowerUp, 41> powerups;
   rstl::vector<std::pair<CAssetId, float>> scan_times;
   std::pair<u32, u32> scan_completion_rate;
   rstl::vector<u8> static_interference;

public:
   bool has_powerup(EItemType power) const {
      return powerups[static_cast<s32>(power)].capacity != 0;
   }
   EPlayerSuit get_suit() const { return current_suit; }
};
#pragma once

#include <type_traits>

#include "freestanding.hh"

enum class EMaterialTypes {
   NoStepLogic = 0,
   Stone = 1,
   Metal = 2,
   Grass = 3,
   Ice = 4,
   Pillar = 5,
   MetalGrating = 6,
   Phazon = 7,
   Dirt = 8,
   Lava = 9,
   LavaStone = 10,
   Snow = 11,
   MudSlow = 12,
   HalfPipe = 13,
   Mud = 14,
   Glass = 15,
   Shield = 16,
   Sand = 17,
   ProjectilePassthrough = 18,
   Solid = 19,
   NoPlatformCollision = 20,
   CameraPassthrough = 21,
   Wood = 22,
   Organic = 23,
   NoEdgeCollision = 24,
   RedundantEdgeOrFlippedTri = 25,
   SeeThrough = 26,
   ScanPassthrough = 27,
   AIPassthrough = 28,
   Ceiling = 29,
   Wall = 30,
   Floor = 31,
   Player = 32,
   Character = 33,
   Trigger = 34,
   Projectile = 35,
   Bomb = 36,
   GroundCollider = 37,
   NoStaticCollision = 38,
   Scannable = 39,
   Target = 40,
   Orbit = 41,
   Occluder = 42,
   Immovable = 43,
   Debris = 44,
   PowerBomb = 45,
   Unknown46 = 46,
   CollisionActor = 47,
   AIBlock = 48,
   Platform = 49,
   NonSolidDamageable = 50,
   RadarObject = 51,
   PlatformSlave = 52,
   AIJoint = 53,
   Unknown54 = 54,
   SolidCharacter = 55,
   ExcludeFromLineOfSightTest = 56,
   ExcludeFromRadar = 57,
   NoPlayerCollision = 58,
   SixtyThree = 63
};

using CMaterialList = u64;

template <typename... Ts>
constexpr CMaterialList cons_matlist(Ts... types) {
   static_assert((std::is_same_v<Ts, EMaterialTypes> && ...),
                 "cons_matlist only accepts EMaterialTypes");
   return CMaterialList{0} | ((CMaterialList{1} << static_cast<uint32_t>(types)) | ...);
}

enum class FilterType { Always, Include, Exclude, IncludeExclude };

struct CMaterialFilter {
   CMaterialList include = 0;
   CMaterialList exclude = 0;
   FilterType filter_type = FilterType::IncludeExclude;

   constexpr CMaterialFilter(CMaterialList const& include, CMaterialList const& exclude,
                             FilterType filter_type)
       : include(include), exclude(exclude), filter_type(filter_type) {}

   static constexpr CMaterialFilter make_include_exclude(CMaterialList const& include,
                                                         CMaterialList const& exclude) {
      return CMaterialFilter(include, exclude, FilterType::IncludeExclude);
   }

   static constexpr CMaterialFilter make_include(CMaterialList const& include) {
      return CMaterialFilter(include, CMaterialList(), FilterType::Include);
   }

   static constexpr CMaterialFilter make_exclude(CMaterialList const& exclude) {
      return CMaterialFilter(CMaterialList{0x00000000ffffffff}, exclude, FilterType::Exclude);
   }
};

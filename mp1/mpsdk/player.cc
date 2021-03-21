#include "mp1/mpsdk/player.hh"

#include "mp1/mpsdk/player_tweak.hh"
#include "mp1/mpsdk/state_manager_min.hh"

ESurfaceRestraints CPlayer::get_surface_restraint(float underwater_move_depth) const {
   if (out_of_water_ticks == 2) {
      return surface_restraint;
   }
   EPlayerSuit suit = CStateManager::instance()->get_player_state()->get_suit();
   switch (suit) {
      case EPlayerSuit::Gravity:
      case EPlayerSuit::Phazon:
      case EPlayerSuit::FusionGravity:
      case EPlayerSuit::FusionPhazon:
         return ESurfaceRestraints::Normal;
      default:
         return distance_underwater > underwater_move_depth ? ESurfaceRestraints::Water
                                                            : ESurfaceRestraints::Normal;
   }
}

bool CPlayer::in_morphball() const { return morphball_state != EPlayerMorphBallState::Unmorphed; }

void CPlayer::set_gravity(float g) { CTweakPlayer::instance()->normal_grav_accel = g; }
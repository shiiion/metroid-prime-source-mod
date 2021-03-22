#include "mp1/mpsdk/player.hh"

#include "mp1/mpsdk/player_tweak.hh"
#include "mp1/mpsdk/state_manager_min.hh"

ESurfaceRestraints CPlayer::get_surface_restraint(float underwater_move_depth) const {
   if (out_of_water_ticks == 2) {
      return surface_restraint;
   }
   if (CStateManager::instance()->get_player_state()->has_powerup(EItemType::GravitySuit)) {
      return ESurfaceRestraints::Normal;
   }
   return distance_underwater > underwater_move_depth ? ESurfaceRestraints::Water
                                                      : ESurfaceRestraints::Normal;
}

bool CPlayer::in_morphball() const { return morphball_state != EPlayerMorphBallState::Unmorphed; }

void CPlayer::set_gravity(float g) { CTweakPlayer::instance()->normal_grav_accel = g; }
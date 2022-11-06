#include "mp2/mpsdk/player.hh"

#include "mp2/mpsdk/tweaks.hh"
#include "mp2/mpsdk/state_manager_min.hh"
#include "util/func_caller.hh"

float CPlayer::get_gravity() const { return call_class_func<float>(0x80189b38, this); }

void CPlayer::set_move_state(EPlayerMovementState state, CStateManager& mgr) {
   call_class_func<void, EPlayerMovementState, CStateManager&>(0x80187370, this, state, mgr);
}

ESurfaceRestraints CPlayer::get_surface_restraint(float underwater_move_depth) const {
   if (CStateManager::instance()->get_player_state()->has_powerup(EItemType::GravityBoost)) {
      return ESurfaceRestraints::Normal;
   }
   if ((surface_restraint == ESurfaceRestraints::Water || surface_restraint == ESurfaceRestraints::DarkWater) &&
       water_depth < underwater_move_depth) {
      return ESurfaceRestraints::Normal;
   }
   return surface_restraint;
}

bool CPlayer::in_morphball() const { return morphball_state != EPlayerMorphBallState::Unmorphed; }

void CPlayer::set_gravity(float g) { CTweakPlayer::instance()->set_gravity(g); }

void CPlayer::start_screwattack() {
   call_class_func<void, int>(0x80184294, this, 1);
}

void CPlayer::start_gravboost(CStateManager& mgr) {
   call_class_func<void, CStateManager&>(0x8018381c, this, mgr);
}

void CPlayer::stop_gravboost(CStateManager& mgr) {
   call_class_func<void, CStateManager&>(0x80183648, this, mgr);
}

#include "mp1/mpsdk/player.hh"

#include "mp1/mpsdk/player_tweak.hh"
#include "mp1/mpsdk/state_manager_min.hh"
#include "util/func_caller.hh"

float CPlayer::get_gravity() const { return call_class_func<float>(0x8028835c, this); }

void CPlayer::set_move_state(EPlayerMovementState state, CStateManager& mgr) {
   call_class_func<void, EPlayerMovementState, CStateManager&>(0x802863ec, this, state, mgr);
}

void CPlayer::update_crosshair_state(CFinalInput const& input) {
   call_class_func<void, CFinalInput const&>(0x800184a0, this, input);
}

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

void CPlayer::clear_freelook_state() {
   in_free_look = false;
   look_button_held = false;
   look_analog_held = false;
   horiz_free_look_ang_vel = 0.f;
   vert_free_look_angle_vel = 0.f;
}

void CPlayer::set_gravity(float g) { CTweakPlayer::instance()->normal_grav_accel = g; }
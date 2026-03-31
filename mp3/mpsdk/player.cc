#include "mp3/mpsdk/player.hh"

#include "mp3/mpsdk/tweaks.hh"
#include "util/func_caller.hh"

float CPlayer::get_gravity() const { return call_class_func<float>(0x801786e8, this); }

void CPlayer::set_move_state(EPlayerMovementState state, CStateManager& mgr) {
   call_class_func<void, EPlayerMovementState, CStateManager&>(0x8017aef8, this, state, mgr);
}

bool CPlayer::in_morphball() const { return morphball_state != EPlayerMorphBallState::Unmorphed; }

void CPlayer::set_gravity(float g) { CTweakPlayer::instance()->set_gravity(g); }

void CPlayer::start_screwattack() {
  call_class_func<void, int>(0x8017d1d8, this, 1);
}

#include "mp3/mpsdk/tweaks.hh"

#include "util/func_caller.hh"

extern "C" CTweakGun* _get_gun_tweak();
extern "C" CTweakPowerup* _get_powerup_tweak();

CTweakPlayer* CTweakPlayer::instance() {
   return *call_func<CTweakPlayer**>(0x8015715c);
}

CTweakGun* CTweakGun::instance() {
   return _get_gun_tweak();
}

CTweakPowerup* CTweakPowerup::instance() {
   return _get_powerup_tweak();
}

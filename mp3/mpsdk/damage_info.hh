#pragma once

#include "freestanding.hh"

struct CDamageInfo {
   uint16_t weapon_type;
   bool charged : 1;
   bool comboed : 1;
   bool instant_kill : 1;
   float damage;
   float radius_damage;
   float radius;
   float knockback;

   CDamageInfo(float amt, int type)
       : weapon_type(type),
         charged(false),
         comboed(false),
         instant_kill(false),
         damage(amt),
         radius_damage(amt),
         radius(0),
         knockback(0) {}
};

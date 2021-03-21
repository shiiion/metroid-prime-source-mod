#pragma once

struct CDamageInfo {
   int weapon_type;
   bool charged : 1;
   bool comboed : 1;
   bool instant_kill : 1;
   float damage;
   float radius_damage;
   float radius;
   float knockback;
   bool no_immunity : 1;

   CDamageInfo(float amt, int type)
       : weapon_type(type),
         charged(false),
         comboed(false),
         instant_kill(false),
         damage(amt),
         radius_damage(amt),
         radius(0),
         knockback(0),
         no_immunity(false) {}
};
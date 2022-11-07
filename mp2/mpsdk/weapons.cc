#include "mp2/mpsdk/weapons.hh"

#include "util/r_math.hh"

void CGameProjectile::set_speed(float speed) {
   projectile_vars.velocity = projectile_vars.velocity.normalized() * speed;
}

void CGameProjectile::multiply_speed(float multiplier) { projectile_vars.velocity *= multiplier; }

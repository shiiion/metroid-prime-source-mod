#include "util/r_math.hh"

#include "util/func_caller.hh"

float sqrt(float x) { return call_func<float, float>(0x803f69d8, x); }
float sign(float x) { return x > 0.f ? 1.f : -1.f; }
float __attribute__ ((noinline)) fabs(float x) { asm("fabs 1,1"); return x; }

double __attribute__ ((noinline)) labs(double x) { asm("fabs 1,1"); return x; }

float vec3::magnitude() const { return sqrt(magnitude_sqr()); }
float vec3::xy_magnitude() const { return sqrt(x * x + y * y); }
vec3 vec3::normalized() const {
   float m = 1.f / magnitude();
   return *this * m;
}
void vec3::normalize() {
   float m = 1.f / magnitude();
   *this *= m;
}

mat34::mat34() {
   constexpr float ident[] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0};
   memcpy(m, ident, sizeof(m));
}

mat34::mat34(mat34 const& other) { memcpy(m, other.m, sizeof(m)); }

mat34& mat34::operator=(mat34 const& rhs) {
   memcpy(m, rhs.m, sizeof(m));
   return *this;
}

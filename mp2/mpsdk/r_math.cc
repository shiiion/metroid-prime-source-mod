#include "util/r_math.hh"

#include "util/func_caller.hh"

// float sin(float x) { return call_func<float, float>(0x80394adc, x); }
// float cos(float x) { return call_func<float, float>(0x803943f0, x); }
// float tan(float x) { return call_func<float, float>(0x80394bb4, x); }
// float asin(float x) { return call_func<float, float>(0x80394c4c, x); }
// float acos(float x) { return call_func<float, float>(0x80394c2c, x); }
// float atan2(float x) { return call_func<float, float>(0x80394c6c, x); }
float sqrt(float x) { return call_func<float, float>(0x8001d678, x); }
// float floor(float x) { return call_func<float, float>(0x803944c4, x); }
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

// Not supported for now
// vec3 mat34::operator*(vec3 const& rhs) const {
//    return call_class_func<vec3, vec3 const&>(0x80312ae8, this, rhs);
// }
//
// mat34 mat34::operator*(mat34 const& rhs) const {
//    return call_class_func<mat34, mat34 const&>(0x80312950, this, rhs);
// }
//
// mat34 mat34::scale(float x, float y, float z) {
//    return call_func<mat34, float, float, float>(0x80313208, x, y, z);
// }
//
// mat34 mat34::translate(float x, float y, float z) {
//    return call_func<mat34, float, float, float>(0x80313188, x, y, z);
// }

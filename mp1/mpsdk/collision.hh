#pragma once

#include "freestanding.hh"
#include "mp1/mpsdk/r_math.hh"
#include "util/func_caller.hh"

struct CMRay {
   CMRay(vec3 const& start, vec3 const& end) : start(start), end(end) {
      delta = end - start;
      length = (end - start).magnitude();
      inv_length = 1.f / length;
      dir = delta.normalized();
   }

   vec3 start, end, delta;
   float length, inv_length;
   vec3 dir;
};

u32 ray_aabb_intersection(CMRay const& ray, aabox const& aabb, float& min, float& max) {
   return call_func<u32, CMRay const&, aabox const&, float&, float&>(0x802d2f80, ray, aabb, min,
                                                                     max);
}
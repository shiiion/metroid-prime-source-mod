#pragma once

#include "freestanding.hh"
#include "mp3/mpsdk/materials.hh"
#include "mp3/rstl/vector.hh"
#include "util/r_math.hh"

class CStateManager;

struct CMRay {
   CMRay(vec3 const& start, vec3 const& end);

   vec3 start, end, delta;
   float length, inv_length;
   vec3 dir;
};

struct CRayCastResult {
   float t;
   vec3 point;
   vec3 plane_point;
   float plane_d;
   bool valid;
   u8 craycastresult_padding1[0x7];
   CMaterialList material;
};

u32 ray_aabb_intersection(CMRay const& ray, aabox const& aabb, float& min, float& max);

bool detect_collision_boolean(CStateManager const& mgr, void const* collision_prim, mat34 const& xf,
                              CMaterialFilter const& filter,
                              rstl::reserved_vector<u32, 2048>& near_list);

CRayCastResult ray_static_intersection(CStateManager const& mgr, vec3 const& pos, vec3 const& dir,
                                       float length, CMaterialFilter const& filter);

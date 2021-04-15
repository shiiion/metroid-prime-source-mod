#pragma once

#include "freestanding.hh"
#include "mp1/mpsdk/materials.hh"
#include "mp1/mpsdk/r_math.hh"
#include "mp1/mpsdk/retro_types.hh"
#include "mp1/rstl/vector.hh"

class CStateManager;
class CMaterialFilter;

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
                              rstl::reserved_vector<TUniqueId, 1024>& near_list);

CRayCastResult ray_static_intersection(CStateManager const& mgr, vec3 const& pos, vec3 const& dir,
                                       float length, CMaterialFilter const& filter);

class CCollisionPrimitive {
protected:
   uintptr_t const* vtable;
   u8 ccollisionprimitive_padding1[0x4];
   CMaterialList material;

public:
   CCollisionPrimitive(CMaterialList const& list);
};

class CCollidableAABox : public CCollisionPrimitive {
protected:
   aabox bounding_box;

public:
   CCollidableAABox(CMaterialList const& list, aabox const& bbox);
};
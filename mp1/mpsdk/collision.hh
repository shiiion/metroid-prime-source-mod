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

u32 ray_aabb_intersection(CMRay const& ray, aabox const& aabb, float& min, float& max);

bool detect_collision_boolean(CStateManager const& mgr, void const* collision_prim, mat34 const& xf,
                              CMaterialFilter const& filter,
                              rstl::reserved_vector<TUniqueId, 1024>& near_list);

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
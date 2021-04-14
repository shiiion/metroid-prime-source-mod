#include "mp1/mpsdk/collision.hh"

#include "util/func_caller.hh"

CMRay::CMRay(vec3 const& start, vec3 const& end) : start(start), end(end) {
   delta = end - start;
   length = (end - start).magnitude();
   inv_length = 1.f / length;
   dir = delta.normalized();
}

u32 ray_aabb_intersection(CMRay const& ray, aabox const& aabb, float& min, float& max) {
   return call_func<u32, CMRay const&, aabox const&, float&, float&>(0x802d2f80, ray, aabb, min,
                                                                     max);
}

bool detect_collision_boolean(CStateManager const& mgr, void const* collision_prim, mat34 const& xf,
                              CMaterialFilter const& filter,
                              rstl::reserved_vector<TUniqueId, 1024>& near_list) {
   return call_func<bool, CStateManager const&, void const*, mat34 const&, CMaterialFilter const&,
                    rstl::reserved_vector<TUniqueId, 1024>&>(0x80184614, mgr, collision_prim, xf,
                                                             filter, near_list);
}

CCollisionPrimitive::CCollisionPrimitive(CMaterialList const& list) {
   call_class_func<void, CMaterialList const&>(0x802cf8b4, this, list);
}

CCollidableAABox::CCollidableAABox(CMaterialList const& list, aabox const& bbox)
    : CCollisionPrimitive(list), bounding_box(bbox) {
   vtable = reinterpret_cast<uintptr_t const*>(0x803ecad0);
}
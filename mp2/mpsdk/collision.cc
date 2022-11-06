#include "mp2/mpsdk/collision.hh"

#include "util/func_caller.hh"

CMRay::CMRay(vec3 const& start, vec3 const& end) : start(start), end(end) {
   delta = end - start;
   length = (end - start).magnitude();
   inv_length = 1.f / length;
   dir = delta.normalized();
}

u32 ray_aabb_intersection(CMRay const& ray, aabox const& aabb, float& min, float& max) {
   return call_func<u32, CMRay const&, aabox const&, float&, float&>(0x8028737c, ray, aabb, min,
                                                                     max);
}

bool detect_collision_boolean(CStateManager const& mgr, void const* collision_prim, mat34 const& xf,
                              CMaterialFilter const& filter,
                              rstl::reserved_vector<TUniqueId, 1024>& near_list) {
   return call_func<bool, CStateManager const&, void const*, mat34 const&, CMaterialFilter const&,
                    rstl::reserved_vector<TUniqueId, 1024>&>(0x80127388, mgr, collision_prim, xf,
                                                             filter, near_list);
}

CRayCastResult ray_static_intersection(CStateManager const& mgr, vec3 const& pos, vec3 const& dir,
                                       float length, CMaterialFilter const& filter) {
   return call_func<CRayCastResult, CStateManager const&, vec3 const&, vec3 const&, float,
                    CMaterialFilter const&>(0x80127584, mgr, pos, dir, length, filter);
}

CCollisionPrimitive::CCollisionPrimitive(CMaterialList const& list) {
   call_class_func<void, CMaterialList const&>(0x8028346c, this, list);
}

CCollidableAABox::CCollidableAABox(CMaterialList const& list, aabox const& bbox)
    : CCollisionPrimitive(list), bounding_box(bbox) {
   vtable = reinterpret_cast<uintptr_t const*>(0x803b9140);
}

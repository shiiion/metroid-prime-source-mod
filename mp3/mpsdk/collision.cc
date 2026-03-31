#include "mp3/mpsdk/collision.hh"

#include "mp3/mpsdk/state_manager_min.hh"
#include "util/func_caller.hh"

CMRay::CMRay(vec3 const& start, vec3 const& end) : start(start), end(end) {
   delta = end - start;
   length = (end - start).magnitude();
   inv_length = 1.f / length;
   dir = delta.normalized();
}

u32 ray_aabb_intersection(CMRay const& ray, aabox const& aabb, float& min, float& max) {
   return call_func<u32, CMRay const&, aabox const&, float&, float&>(0x8030fc30, ray, aabb, min,
                                                                     max);
}

bool detect_collision_boolean(CStateManager const& mgr, void const* collision_prim, mat34 const& xf,
                              CMaterialFilter const& filter,
                              rstl::reserved_vector<u32, 2048>& near_list) {
   return call_func<bool, CStateManager const&, void const*, mat34 const&, CMaterialFilter const&,
                    rstl::reserved_vector<u32, 2048>&>(0x8009f640, mgr, collision_prim, xf, filter,
                                                       near_list);
}

CRayCastResult ray_static_intersection(CStateManager const& mgr, vec3 const& pos, vec3 const& dir,
                                       float length, CMaterialFilter const& filter) {
   return call_func<CRayCastResult, void const*, vec3 const&, vec3 const&, float,
                    CMaterialFilter const&>(0x8009f220, &mgr.cdata, pos, dir, length, filter);
}

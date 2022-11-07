#pragma once

#include "mp2/mpsdk/entity.hh"
#include "mp2/mpsdk/materials.hh"
#include "mp2/mpsdk/player_state.hh"
#include "util/r_math.hh"

class CActor : public CEntity {
public:
   mat34 transform; // 24
   vec3 position; // 54
   void* model_data; // 60
   CMaterialList materials __attribute__((packed, aligned(4))); // 64
   CMaterialFilter material_filter; // 6c;
   uint8_t cactor_unk0[0xd8]; // 80 -> 158

public:
   void pre_render(CStateManager& mgr, void* frustum_planes) {
      call_vfunc<void, CStateManager&, void*>(this, 6, mgr, frustum_planes);
   }
   void add_to_renderer(void* frustum_planes, CStateManager& mgr) {
      call_vfunc<void, void*, CStateManager&>(this, 7, frustum_planes, mgr);
   }
   void render(float dt, CStateManager& mgr) {
      call_vfunc<void, float, CStateManager&>(this, 8, dt, mgr);
   }
   bool can_render_unsorted(CStateManager const& mgr) {
      return call_vfunc<bool, CStateManager const&>(this, 9, mgr);
   }
   CHealthInfo* get_health_info(CStateManager& mgr) {
      return call_vfunc<CHealthInfo*, CStateManager&>(this, 12, mgr);
   }
   // Add more as needed...

   mat34 const& get_transform() const { return transform; }
   mat34& get_transform() { return transform; }
   vec3 const& get_position() const { return position; }
   vec3& get_position() { return position; }
   void set_position(vec3 const& pos) { position = pos; }
};

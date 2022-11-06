#pragma once

#include "mp1/mpsdk/entity.hh"
#include "mp1/mpsdk/materials.hh"
#include "mp1/mpsdk/player_state.hh"
#include "util/r_math.hh"

class CActor : public CEntity {
protected:
   mat34 transform;
   void* model_data;
   CMaterialList materials;
   CMaterialFilter material_filter;
   u16 sfx_id;
   u32 sfx_handle;
   void* actor_lights;
   void* simple_shadow;
   void* scan_object_info;
   aabox render_bounds;
   struct {
      u8 blend_mode;
      u8 mat_set_idx;
      u16 flags;
      u32 color;
   } model_flags;
   float time;
   float pitch_bend;
   TUniqueId fluid_id;
   TUniqueId next_draw_node;
   int draw_token;
   int added_token;
   float damage_mag;
   float max_vol;
   u8 non_looping_sfx_handles[0xc];
#pragma pack(push, 1)
   struct {
      u8 next_non_looping_sfx_handle : 3;
      bool not_in_sorted_lists : 1;
      bool transform_dirty : 1;
      bool actor_lights_dirty : 1;
      bool out_of_frustrum : 1;
      bool calculate_lighting : 1;
      bool shadow_enabled : 1;
      bool shadow_dirty : 1;
      bool muted : 1;
      bool use_in_sorted_lists : 1;
      bool call_touch : 1;
      bool global_time_provider : 1;
      bool render_unsorted : 1;
      bool point_generator_particles : 1;
      u8 fluid_counter : 3;
      u8 thermal_visor_flags : 2;
      bool render_particle_db_inside : 1;
      bool enable_pitch_blend : 1;
      u8 targetable_visor_flags : 4;  // why am aligned, bitfield? ?? ?
      bool enable_render : 1;
      bool world_lighting_dirty : 1;
      bool draw_enabled : 1;
      bool do_target_distance_test : 1;
      bool targetable : 1;
   };
#pragma pack(pop)

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
      return call_vfunc<CHealthInfo*, CStateManager&>(this, 10, mgr);
   }
   // Add more as needed...

   mat34 const& get_transform() const { return transform; }
   mat34& get_transform() { return transform; }
};

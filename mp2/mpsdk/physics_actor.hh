#pragma once

#include "mp2/mpsdk/actor.hh"
#include "mp2/rstl/optional.hh"
#include "util/r_math.hh"

struct CMotionState {
   vec3 translation;
   vec4 orientation_quat;
   vec3 velocity;
   vec3 angular_momentum;
};

class CPhysicsActor : public CActor {
protected:
   float mass; // 158
   float inv_mass; // 15c
   float inertia_tensor; // 160
   float inv_inertia_tensor; // 164
   struct { // 168
      bool movable : 1;
      bool angular_enabled : 1;
   };
   bool standard_collider; // 169
   vec3 constant_force; // 16c
   vec3 angular_momentum; // 178
   mat3 unk; // 184
   vec3 velocity; // 1a8
   vec3 angular_velocity; // 1b4
   vec3 momentum; // 1c0
   vec3 force; // 1cc
   vec3 impulse; // 1d8
   vec3 torque; // 1e4
   vec3 angular_impulse; // 1f0
   vec3 move_impulse; // 1fc
   vec3 move_angular_impulse; // 208
   aabox base_bounding_box; // 214
   uint8_t cphysicsactor_unk0[0x4];
   struct { // 230
      uintptr_t const* const vtable; // 230
      u8 unk1[4]; // 234
      CMaterialList materials; // 238
      aabox bbox; // 240
   } collision_primitive;
   vec3 primitive_offset; // 258
   CMotionState last_noncolliding_state; // 264
   rstl::optional<vec3> last_floor_plane_normal; // 298
   float maximum_collision_velocity; // 2a8
   float step_up_height; // 2ac
   float step_down_height; // 2b0
   float restitution_coefficient_modifier; // 2b4
   float collision_accuracy_modifier; // 2b8
   u32 num_ticks_stuck; // 2bc
   u32 num_ticks_partial_update; // 2c0
   u8 cphysicsactor_unk1[0xc]; // 0x2c4

public:
   vec3 const& get_velocity() const { return velocity; }
   vec3& get_velocity() { return velocity; }
   void add_velocity(vec3 const& v) { velocity += v; }

   void set_velocity_wr(vec3 const& vel) {
      call_class_func<void, vec3 const&>(0x800ea404, this, vel);
   }
   void set_velocity_or(vec3 const& vel) {
      call_class_func<void, vec3 const&>(0x800ea47c, this, vel);
   }

   aabox const& get_collision_bounds() const { return collision_primitive.bbox; }
   aabox& get_collision_bounds() { return collision_primitive.bbox; }
   // add more as needed...
};

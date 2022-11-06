#pragma once

#include "mp1/mpsdk/actor.hh"
#include "mp1/rstl/optional.hh"
#include "util/r_math.hh"

struct CMotionState {
   vec3 translation;
   vec4 orientation_quat;
   vec3 velocity;
   vec3 angular_momentum;
};

class CPhysicsActor : public CActor {
protected:
   float mass;
   float inv_mass;
   float inertia_tensor;
   float inv_inertia_tensor;
   struct {
      bool movable : 1;
      bool angular_enabled : 1;
   };
   bool standard_collider;
   vec3 constant_force;
   vec3 angular_momentum;
   mat3 unk;
   vec3 velocity;
   vec3 angular_velocity;
   vec3 momentum;
   vec3 force;
   vec3 impulse;
   vec3 torque;
   vec3 angular_impulse;
   vec3 move_impulse;
   vec3 move_angular_impulse;
   aabox base_bounding_box;
   struct {
      uintptr_t const* const vtable;
      u8 unk1[4];
      CMaterialList materials;
      aabox bbox;
   } collision_primitive;
   vec3 primitive_offset;
   CMotionState last_noncolliding_state;
   rstl::optional<vec3> last_floor_plane_normal;
   float maximum_collision_velocity;
   float step_up_height;
   float step_down_height;
   float restitution_coefficient_modifier;
   float collision_accuracy_modifier;
   u32 num_ticks_stuck;
   u32 num_ticks_partial_update;
   u8 cphysicsactor_padding1[0x4];

public:
   vec3 const& get_velocity() const { return velocity; }
   vec3& get_velocity() { return velocity; }
   void add_velocity(vec3 const& v) { velocity += v; }

   void set_velocity_wr(vec3 const& vel) {
      call_class_func<void, vec3 const&>(0x8011aca0, this, vel);
   }
   void set_velocity_or(vec3 const& vel) {
      call_class_func<void, vec3 const&>(0x8011ad18, this, vel);
   }

   aabox const& get_collision_bounds() const { return collision_primitive.bbox; }
   aabox& get_collision_bounds() { return collision_primitive.bbox; }
   // add more as needed...
};

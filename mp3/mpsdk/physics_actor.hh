#pragma once

#include "mp3/mpsdk/actor.hh"
#include "mp3/mpsdk/materials.hh"
#include "util/r_math.hh"

class CPhysicsActor : public CActor {
protected:
   float mass; // 154
   uint8_t cphysicsactor_unk0[0x14]; // 158 -> 16c
   vec3 angular_momentum; // 16c
   vec3 velocity; // 178
   vec3 angular_velocity; // 184
   uint8_t cphysicsactor_unk1[0x70]; // 190 -> 200
   struct { // 200
      uintptr_t const* const vtable; // 200
      u8 unk1[4]; // 204
      CMaterialList materials; // 208
      aabox bbox; // 210
   } collision_primitive;
   uint8_t cphysicsactor_unk2[0x74]; // 228 -> 29c

public:
   float get_mass() const { return mass; }
   vec3 const& get_velocity() const { return velocity; }
   vec3& get_velocity() { return velocity; }
   void add_velocity(vec3 const& v) { velocity += v; }

   vec3 const& get_angular_velocity() const { return angular_velocity; }
   void set_angular_velocity(vec3 const& avel) { angular_velocity = avel; }
   void set_angular_momentum(vec3 const& amom) { angular_momentum = amom; }

   void set_velocity_wr(vec3 const& vel) {
      call_class_func<void, vec3 const&>(0x80138f14, this, vel);
   }

   aabox const& get_collision_bounds() const { return collision_primitive.bbox; }
   aabox& get_collision_bounds() { return collision_primitive.bbox; }
   void* get_collision_prim() { return &collision_primitive; }
};

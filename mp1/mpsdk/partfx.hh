#pragma once

#include "freestanding.hh"
#include "mp1/mpsdk/r_math.hh"
#include "mp1/mpsdk/retro_types.hh"
#include "mp1/mpsdk/token.hh"
#include "mp1/rstl/vector.hh"

class CGenDescription;
class CModVectorElement;

enum class EModelOrientationType { Normal, One };
enum class ELightType { None = 0, Custom = 1, Directional = 2, Spot = 3 };
// Belongs to CLight
enum class EFalloffType { Constant, Linear, Quadratic };

struct CParticle {
   int end_frame;
   vec3 pos;
   vec3 prev_pos;
   vec3 vel;
   int start_frame;
   float line_length_or_size;
   float line_width_or_rota;
   CColor color;
};

class CParticleGen {
protected:
   uintptr_t const* const vtable;
   u8 unused__warp_list[0x18];

public:
   NO_INSTANTIATE(CParticleGen);
   void destroy_and_free();
};

class CElementGen : public CParticleGen {
private:
   TCachedToken<CGenDescription*> gen_desc;
   CGenDescription* loaded_gen_desc;
   EModelOrientationType orient_type;
   rstl::vector<CParticle> particles;
   rstl::vector<u32> celementgen_unk1;
   rstl::vector<mat3> parent_matrices;
   rstl::vector<float[8]> adv_values;
   int internal_start_frame;
   int cur_frame;
   double cur_seconds;
   float time_delta_scale;
   int prev_frame;
   bool particle_emission;
   float generator_remainder;
   int maxp;
   u16 random_seed;
   float generator_rate;
   float external_vars[16];
   vec3 translation;
   vec3 global_translation;
   vec3 POFS;
   vec3 global_scale;
   mat34 global_scale_transform;
   mat34 global_scale_transform_inv;
   vec3 local_scale;
   mat34 local_scale_transform;
   mat34 local_scale_transform_inv;
   mat34 orientation;
   mat3 orientation_inv;
   mat34 global_orientation;

   u32 active_particle_count;
   u32 cumulative_particles;
   u32 recursive_particle_count;
   int PSLT;
   bool translation_dirty : 1;
   bool LIT_ : 1;
   bool AAPH : 1;
   bool ZBUF : 1;
   bool z_test : 1;
   bool ORNT : 1;
   bool MBLR : 1;
   bool LINE : 1;
   bool FXLL : 1;
   bool warmed_up : 1;
   bool models_use_lights : 1;
   bool enable_OPTS : 1;
   bool enable_ADV : 1;
   int MBSP;
   u32 backup_light_active;
   bool has_VMD[4];
   CRandom16 rand_state;
   CModVectorElement* VEL_sources[4];

   rstl::vector<CParticleGen*> active_children;
   int CSSD;
   int SISY;
   int PISY;
   int SSSD;
   vec3 SSPO;
   int SESD;
   vec3 SEPO;
   float celementgen_unk2;
   float celementgen_unk3;
   vec3 aabb_min;
   vec3 aabb_max;
   float max_size;
   aabox system_bounds;
   ELightType light_type;
   CColor LCLR;
   float LINT;
   vec3 LOFF;
   vec3 LDIR;
   EFalloffType falloff_type;
   float LFOR;
   float LSLA;
   CColor modu_color;

public:
   NO_INSTANTIATE(CElementGen);

   void reset_generator();
   void original_update(double dt) { call_class_func<void, double>(0x8031EA90, this, dt); }
};
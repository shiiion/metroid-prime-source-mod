#include "mp1/mod_shared.hh"
#include "mp1/mpsdk/os.hh"
#include "mp1/mpsdk/partfx.hh"
#include "mp1/mpsdk/random.hh"

class CElementGenFix : public CElementGen {
public:
   bool internal_update_psts_fix(double dt) {
      constexpr double epsilon = 1.0 / 60000.0;
      dt = kNormalDtLong;

      u64 start_time = os_get_time();
      CGlobalRandom rand(rand_state);

      double dt_scaled = dt;
      double cur_frame_time = static_cast<double>(cur_frame) * kNormalDtLong;
      int iteration_count = 0;

      // CParticleGlobals::SetEmitterTime
      call_func<void, int>(0x8032a748, cur_frame);

      if (auto* psts_element = loaded_gen_desc->PSTS) {
         float psts_val = 1.f;
         psts_element->get_value(cur_frame, psts_val);
         dt_scaled *= psts_val;
         dt_scaled = max(dt_scaled, 0.0);
      }
      dt_scaled *= game_timescale;
      dt_scaled = max(dt_scaled, 0.0);

      cur_seconds += dt_scaled;

      // x26c_30_MBLR
      if (MBLR && dt > 0.0) {
         if (auto* mbsp_element = loaded_gen_desc->MBSP) {
            mbsp_element->get_value(cur_frame, MBSP);
         }
      }

      // Ghetto fix, move UpdateChildParticleSystems here, as
      // at least all ElementGens should run the same scaling logic
      // CElementGen::UpdateChildParticleSystems
      call_class_func<void, double>(0x8031c9b4, this, kNormalDtLong);

      while (cur_frame_time < cur_seconds && labs(cur_frame_time - cur_seconds) >= epsilon) {
         aabb_min = vec3(FLT_MAX, FLT_MAX, FLT_MAX);
         aabb_max = vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
         max_size = 0.f;
         // CParticleGlobals::SetEmitterTime
         call_func<void, int>(0x8032a748, cur_frame);
         // CElementGen::UpdateExistingParticles
         call_class_func<void>(0x8031dd6c, this);
         // CParticleGlobals::SetParticleLifetime
         call_func<void, int>(0x8032A778, PSLT);

         // x88_particleEmission
         if (cur_frame < PSLT && particle_emission) {
            float grte_val = 0;
            auto* grte_element = loaded_gen_desc->GRTE;
            if (grte_element->get_value(cur_frame, grte_val)) {
               // clear particles
               particles.clear();
               return true;
            }
            grte_val = max(0.f, generator_rate * grte_val);
            generator_remainder += grte_val;
            // floor
            int gen_count = static_cast<int>(floor(generator_remainder));
            generator_remainder -= static_cast<float>(gen_count);

            // update MAXP val
            if (auto* maxp_element = loaded_gen_desc->MAXP) {
               maxp_element->get_value(cur_frame, MAXP);
            }

            // CElementGen::CreateNewParticles
            call_class_func<void, int>(0x8031d6e4, this, gen_count);
         }

         // TranslationDirty
         if (translation_dirty) {
            // CElementGen::UpdatePSTranslationAndOrientation
            call_class_func<void>(0x8031d620, this);
         }
         if (light_type != ELightType::None) {
            call_class_func<void>(0x8031e53c, this);
         }

         cur_frame_time += dt;
         cur_frame++;
         iteration_count++;
      }

      if (labs(cur_frame_time - cur_seconds) >= epsilon) {
         // This was screwing things up pretty bad, so no more
         // double update_dt = dt_scaled - (static_cast<double>(iteration_count) / 60.0);
         // call_class_func<void, double>(0x8031c9b4, this, update_dt);
         time_delta_scale = 1.f - static_cast<float>((cur_frame_time - cur_seconds) / dt);
      } else {
         cur_seconds = cur_frame_time;
         time_delta_scale = 1.f;
      }

      // CElementGen::BuildParticleSystemBounds
      call_class_func<void>(0x80317a1c, this);

      update_runtime = compute_elapsed(start_time, os_get_time());
      return false;
   }
};

extern "C" {
void hooked_elementgen_update(CElementGen* element_gen, double dt) {
   if (dt_just_changed) {
      // Destroy particles
      element_gen->reset_generator();
   }
   element_gen->original_update(dt);
}

bool hooked_internalupdate(CElementGen* element_gen, double dt) {
   return static_cast<CElementGenFix*>(element_gen)->internal_update_psts_fix(dt);
}
}
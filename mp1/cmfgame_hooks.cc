#include "freestanding.hh"
#include "mp1/mod_shared.hh"
#include "mp1/mpsdk/cmfgame.hh"
#include "mp1/mpsdk/partfx.hh"
#include "mp1/mpsdk/text_support.hh"
#include "mp1/mpsdk/os.hh"

constexpr float kNormalDt = 1.f / 60.f;

bool dt_just_changed = false;
static CGuiTextSupport* ingame_debug_text = nullptr;
static float last_dt = kNormalDt;
static LogToken delta_time_token = kInvalidToken;
float mod_curtime = 0.f;

// Exposed mod cvars
extern "C" {
float game_timescale = 1.f;
bool show_logs = false;
}

extern "C" {
using reg_ctx = u32[18];
extern void _save_reg_ctx(volatile reg_ctx);
extern void _restore_reg_ctx(volatile reg_ctx);
}

extern char debug_output[4096];

void update_dt_changed_flag(float dt) {
   dt_just_changed = (dt != last_dt);
   last_dt = dt;
}
static void ensure_logging_init() {
   if (ingame_debug_text == nullptr) {
      ingame_debug_text = CGuiTextSupport::create_debug_print(0.5f);
   }
   if (delta_time_token == kInvalidToken) {
      delta_time_token = generate_debug_log_token();
   }
}

// Exposed mod functions
extern "C" {
void hooked_elementgen_update(CElementGen* element_gen, double dt) {
   if (dt_just_changed) {
      // Destroy particles
      element_gen->reset_generator();
   }
   element_gen->original_update(dt);
}

/*
struct CGlobalRandom {
   void* random;
   bool unk;
   CGlobalRandom* prev;

   CGlobalRandom(void* rand) { ((void (*)(void*, void*))0x80312680)(this, rand); }
   ~CGlobalRandom() { ((void (*)(void*, int))0x80312604)(this, -1); }
};
bool hooked_internalupdate(char* partgen, double dt) {
  constexpr double part_frame_rate = 1.0 / 60.0;
  constexpr double epsilon = 1.0 / 60000.0;

  uint64_t start_time = ((uint64_t(*)())0x803853A8)();
  CGlobalRandom rand(partgen + 0x27c);

  int& cur_frame = *(int*)(partgen + 0x74);
  double cur_frame_time = double{cur_frame} * part_frame_rate;
  int iteration_count = 0;

  // CParticleGlobals::SetEmitterTime
  ((void(*)(int))0x8032A748)(cur_frame);

  if (char* psts_element = ((char***)partgen)[10][2]) {
    float psts = 1.f;
    // psts->GetValue
    ((void(*)(void*, int, float&))((u32**)psts_element)[0][3])(psts_element, cur_frame, psts);
    dt *= psts;
    dt = max(dt, 0.0);
  }

  double& cur_seconds = *(double*)(partgen + 0x78);
  cur_seconds += dt;

  // x26c_30_MBLR
  if (bit_check(*(u8*)(partgen + 0x26c), 1) && dt > 0.0) {
    if (char* mbsp_element = ((char***)partgen)[10][13]) {
      // mbsp->GetValue --> x270_MBSP
      ((void(*)(void*, int, float*))((u32**)mbsp_element)[0][3])(mbsp_element, cur_frame,
(float*)(partgen + 0x270));
    }
  }

  while (cur_frame_time < cur_seconds && abs(cur_frame_time - cur_seconds) >= epsilon) {
    *(vec3*)(partgen + 0x2d4) = vec3(FLT_MAX, FLT_MAX, FLT_MAX);
    *(vec3*)(partgen + 0x2e0) = vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    *(float*)(partgen + 0x2ec) = 0.f;
    // CParticleGlobals::SetEmitterTime
    ((void(*)(int))0x8032A748)(cur_frame);
    // CElementGen::UpdateExistingParticles
    ((void(*)(void*))0x8031DD6C)(partgen);
    int pslt = *(int*)(partgen + 0x268);
    // CParticleGlobals::SetParticleLifetime
    ((void(*)(int))0x8032A778)(pslt);

    // x88_particleEmission
    if (cur_frame < pslt && *(u8*)(partgen + 0x88)) {
      float grte = 0;
      char* grte_element = ((char***)partgen)[10][8];
      if (((bool(*)(void*, int, float&))((u32**)grte_element)[0][3])(grte_element, cur_frame, grte))
{
        // clear particles
        *(u32*)(partgen + 0x34) = 0;
        return true;
      }
      grte = max(0.f, *(float*)(partgen + 0x98) * grte);
      *(float*)(partgen + 0x8c) += grte;
      // floor
      int gen_count = int{((float(*)(float))0x803944C4)(*(float*)(partgen + 0x8c))};
      *(float*)(partgen + 0x8c) -= float{gen_count};

      // update MAXP val
      if (char* maxp_element = ((char***)partgen)[10][7]) {
        ((void(*)(void*, int, float*))((u32**)maxp_element)[0][3])(maxp_element, cur_frame,
(float*)(partgen + 0x90));
      }

      // CElementGen::CreateNewParticles
      ((void(*)(void*, int))0x8031D6E4)(partgen, gen_count);
    }

    // TranslationDirty
    if (bit_check(*(u8*)(partgen + 0x26c), 7)) {
      // CElementGen::UpdatePSTranslationAndOrientation
      ((void(*)(void*))0x8031D620)(partgen);
    }
    if (*(int*)(partgen + 0x308) != 0) {
      ((void(*)(void*))0x8031E53C)(partgen);
    }

    // CElementGen::UpdateChildParticleSystems
    ((void(*)(void*, double))0x8031C9B4)(partgen, dt);

    cur_frame_time += dt;
    int old_cur_frame = cur_frame;
    cur_frame = int{cur_frame_time * 60.0};
    iteration_count += cur_frame - old_cur_frame;
  }

  if (abs(cur_frame_time - cur_seconds) >= epsilon) {
    double update_dt = dt - (double{iteration_count} * dt);
    ((void(*)(void*, double))0x8031C9B4)(partgen, update_dt);
    *(float*)(partgen + 0x80) = 1.f - float{(cur_frame_time - cur_seconds) / dt};
  } else {
    cur_seconds = cur_frame_time;
    *(float*)(partgen + 0x80) = 1.f;
  }

  // CElementGen::BuildParticleSystemBounds
  ((void(*)(void*))0x80317A1C)(partgen);

  uint64_t elapsed_time = ((uint64_t(*)())0x803853A8)() - start_time;
  float elapsed_flt = ((float(*)(uint64_t))0x80389F64)(elapsed_time);
  *(float*)(partgen + 0x2cc) = *(float*)(0x8059FD40) * elapsed_flt;
  return false;
}
*/

int hooked_cmfgame_onmessage(CMFGame* cmfgame, CArchitectureMessage* arch_message,
                             void* arch_queue) {
   EArchMsgType message_type = arch_message->type;
   const float scaled_dt = (1.f / 60.f) * game_timescale;

   // Create the debug printer
   ensure_logging_init();

   if (message_type == EArchMsgType::TimerTick) {
      update_dt_changed_flag(scaled_dt);
      arch_message->get_param_val<float>() = scaled_dt;

      char scaled_dt_fmt[128];
      sprintf(scaled_dt_fmt, "dt = %.4f, timescale = %.4f", scaled_dt, game_timescale);
      log_on_token(delta_time_token, scaled_dt_fmt);
   } else if (message_type == EArchMsgType::UserInput) {
      arch_message->get_param_val<float>() = scaled_dt;
   }
   // fix stupid dumb hardcoding in particle systems
   *(double*)(0x805a88b0) = double{scaled_dt};

   // fucking stupid code warrior garbage has decided NOT to save registers
   // so thanks, great, now I've got to resort to this shit, but that's fine
   // and dandy i love this
   volatile reg_ctx saved_regs;
   _save_reg_ctx(saved_regs);
   volatile int iowin_return_code = cmfgame->original_onmessage(arch_message, arch_queue);
   _restore_reg_ctx(saved_regs);

   if (message_type == EArchMsgType::TimerTick) {
      if (ingame_debug_text != nullptr && show_logs) {
         ingame_debug_text->set_text(get_log_string());
         ingame_debug_text->update(scaled_dt);
      }
   }
   return iowin_return_code;
}

void hooked_cmfgame_draw(CMFGame* cmfgame) {
   cmfgame->original_draw();
   if (ingame_debug_text != nullptr && show_logs) {
      ingame_debug_text->prepare_for_render();
      ingame_debug_text->render();
   }
}
}
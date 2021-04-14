#include "freestanding.hh"
#include "mp1/mod_shared.hh"
#include "mp1/mpsdk/cmfgame.hh"
#include "mp1/mpsdk/text_support.hh"
#include "mp1/mpsdk/alloc.hh"

bool dt_just_changed = false;
static CGuiTextSupport* ingame_debug_text = nullptr;
static float last_dt = kNormalDt;
static LogToken delta_time_token = kInvalidToken;

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

void update_dt_changed_flag(float dt) {
   dt_just_changed = (dt != last_dt);
   last_dt = dt;
}

void cmfgame_hooks_release() {
   if (ingame_debug_text != nullptr) {
      ingame_debug_text->destroy();
      free(ingame_debug_text);
      ingame_debug_text = nullptr;
   }
   delta_time_token = kInvalidToken;
}

// Don't free
void cmfgame_hooks_suspend() {}

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
int hooked_cmfgame_onmessage(CMFGame* cmfgame, CArchitectureMessage* arch_message,
                             void* arch_queue) {
   EArchMsgType message_type = arch_message->type;
   const float scaled_dt = kNormalDt * game_timescale;

   // Create the debug printer
   ensure_logging_init();

   if (message_type == EArchMsgType::TimerTick) {
      update_dt_changed_flag(scaled_dt);
      arch_message->get_param_val<float>() = scaled_dt;

      if (show_logs) {
         char scaled_dt_fmt[128];
         sprintf(scaled_dt_fmt, "dt = %.4f, timescale = %.4f", scaled_dt, game_timescale);
         log_on_token(delta_time_token, scaled_dt_fmt);
      }
   } else if (message_type == EArchMsgType::UserInput) {
      arch_message->get_param_val<float>() = scaled_dt;
   }

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
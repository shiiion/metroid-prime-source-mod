#include "mp1/mod_shared.hh"

#include "mp1/rstl/vector.hh"

static rstl::reserved_vector<rstl::string, 16> log_lines;

LogToken generate_debug_log_token() {
   LogToken tok = static_cast<LogToken>(log_lines.size());
   if (tok == log_lines.capacity()) {
      return kInvalidToken;
   }
   log_lines.push_back(rstl::string());
   return tok;
}

void log_on_token(LogToken tok, rstl::string const& str) {
   if (tok == kInvalidToken) {
      return;
   }

   const size_t tok_idx = static_cast<size_t>(tok);
   if (tok_idx >= log_lines.size()) {
      return;
   }

   log_lines[tok_idx] = str;
}

rstl::string get_log_string() {
   rstl::string out_str;
   for (rstl::string const& line : log_lines) {
      // Inefficient oaaeae
      out_str.append(line + "\n");
   }
   return out_str;
}

extern "C" {
int shutdown_signal = 0;
void release_mod() {
   if (shutdown_signal == 1) {
      log_lines.clear();
      cmfgame_hooks_release();
      compute_movement_release();
      rocket_jump_release();
      partfx_timescale_release();
      shutdown_signal = 2;
   } else if (shutdown_signal == 3) {
      cmfgame_hooks_suspend();
      compute_movement_suspend();
      rocket_jump_suspend();
      partfx_timescale_suspend();
      shutdown_signal = 4;
   }
}
}
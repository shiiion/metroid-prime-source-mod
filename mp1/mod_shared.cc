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
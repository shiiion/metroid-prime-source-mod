#include "mp2/mpsdk/input.hh"

#include "util/func_caller.hh"

float get_analog_input(rstl::reserved_vector<bool, 0x4c> const& input_mask, ECommands command, CFinalInput* input) {
   return call_func<float, rstl::reserved_vector<bool, 0x4c> const&, ECommands, CFinalInput*, int>(0x80009d18, input_mask, command, input, 0);
}

bool get_digital_input(rstl::reserved_vector<bool, 0x4c> const& input_mask, ECommands command, CFinalInput* input) {
   return call_func<bool, rstl::reserved_vector<bool, 0x4c> const&, ECommands, CFinalInput*, int>(0x80009c84, input_mask, command, input, 0);
}

bool get_press_input(rstl::reserved_vector<bool, 0x4c> const& input_mask, ECommands command, CFinalInput* input) {
   return call_func<bool, rstl::reserved_vector<bool, 0x4c> const&, ECommands, CFinalInput*, int>(0x80009bf0, input_mask, command, input, 0);
}

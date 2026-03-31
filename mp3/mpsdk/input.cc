#include "mp3/mpsdk/input.hh"

#include "util/func_caller.hh"

float get_analog_input(void* input_mask, ECommands command, CFinalInput* input) {
   return call_func<float, void*, ECommands, CFinalInput*, int>(0x80061ba8, input_mask, command, input, 0);
}

bool get_digital_input(void* input_mask, ECommands command, CFinalInput* input) {
   return call_func<bool, void*, ECommands, CFinalInput*, int>(0x800621c4, input_mask, command, input, 0);
}

bool get_press_input(void* input_mask, ECommands command, CFinalInput* input) {
   return call_func<bool, void*, ECommands, CFinalInput*, int>(0x8006244c, input_mask, command, input, 0);
}

bool is_dpad_up_pressed(CFinalInput* input) { 
  return reinterpret_cast<bool*>(input)[0x10c];
}

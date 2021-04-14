#include "mp1/mpsdk/input.hh"

#include "util/func_caller.hh"

float get_analog_input(ECommands command, CFinalInput* input) {
   return call_func<float, ECommands, CFinalInput*>(0x8000c918, command, input);
}

bool get_digital_input(ECommands command, CFinalInput* input) {
   return call_func<bool, ECommands, CFinalInput*>(0x8000c874, command, input);
}

bool get_press_input(ECommands command, CFinalInput* input) {
   return call_func<bool, ECommands, CFinalInput*>(0x8000c7d0, command, input);
}
#pragma once

enum class ECommands {
   Forward = 0,
   Backward,
   StrafeLeft = 6,
   StrafeRight,
   Jump,
};

class CFinalInput;

float get_analog_input(void* input_mask, ECommands command, CFinalInput* input);
bool get_digital_input(void* input_mask, ECommands command, CFinalInput* input);
bool get_press_input(void* input_mask, ECommands command, CFinalInput* input);

bool is_dpad_up_pressed(CFinalInput* input);

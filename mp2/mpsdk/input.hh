#pragma once

#include "mp2/rstl/vector.hh"

enum class ECommands {
   Unknown = 0,
   Forward = 1,
   Backward,
   TurnOrLookLeft,
   TurnOrLookRight,
   StrafeLeft,
   StrafeRight,
   Unknown2,
   Unknown3,
   LookUp,
   LookDown,
   Jump1,
   Jump2,
   FireOrBomb1,
   FireOrBomb2, // 0xe
   // Unknown 0xf-0x11
   Missile = 0x12,
   // Unknown 0x13-0x17
   PowerBeam = 0x18,
   DarkBeam,
   LightBeam,
   AnnihilatorBeam,
   Lockon1 = 0x1e,
   Lockon2,
   Freelook = 0x26
};

class CFinalInput;

float get_analog_input(rstl::reserved_vector<bool, 0x4c> const& input_mask, ECommands command, CFinalInput* input);
bool get_digital_input(rstl::reserved_vector<bool, 0x4c> const& input_mask, ECommands command, CFinalInput* input);
bool get_press_input(rstl::reserved_vector<bool, 0x4c> const& input_mask, ECommands command, CFinalInput* input);

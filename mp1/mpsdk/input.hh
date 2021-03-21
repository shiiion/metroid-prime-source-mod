#pragma once

#include "util/func_caller.hh"

enum class ECommands {
   Forward,
   Backward,
   TurnLeft,
   TurnRight,
   StrafeLeft,
   StrafeRight,
   LookLeft,
   LookRight,
   LookUp,
   LookDown,
   JumpOrBoost = 10,
   FireOrBomb = 11,
   MissileOrPowerBomb = 12,
   Morph,
   AimUp,
   AimDown,
   CycleBeamUp,
   CycleBeamDown,
   CycleItem,
   PowerBeam,
   IceBeam,
   WaveBeam,
   PlasmaBeam,
   ToggleHolster = 23,
   OrbitClose,
   OrbitFar,
   OrbitObject,
   OrbitSelect,
   OrbitConfirm,
   OrbitLeft,
   OrbitRight,
   OrbitUp,
   OrbitDown,
   LookHold1,
   LookHold2,
   LookZoomIn,
   LookZoomOut,
   AimHold,
   MapCircleUp,
   MapCircleDown,
   MapCircleLeft,
   MapCircleRight,
   MapMoveForward,
   MapMoveBack,
   MapMoveLeft,
   MapMoveRight,
   MapZoomIn,
   MapZoomOut,
   SpiderBall,
   ChaseCamera,
   XrayVisor = 50,
   ThermoVisor = 51,
   InviroVisor = 52,
   NoVisor = 53,
   VisorMenu,
   VisorUp,
   VisorDown,
   ShowCrosshairs,
   UseSheild = 0x3B,
   ScanItem = 0x3C,
   PreviousPauseScreen = 0x41,
   NextPauseScreen = 0x42,
   UNKNOWN,
   None,
   MAX
};

class CFinalInput;

float get_analog_input(ECommands command, CFinalInput* input) {
   return call_func<float, ECommands, CFinalInput*>(0x8000c918, command, input);
}
bool get_digital_input(ECommands command, CFinalInput* input) {
   return call_func<bool, ECommands, CFinalInput*>(0x8000c874, command, input);
}
bool get_press_input(ECommands command, CFinalInput* input) {
   return call_func<bool, ECommands, CFinalInput*>(0x8000c7d0, command, input);
}
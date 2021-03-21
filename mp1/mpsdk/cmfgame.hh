#pragma once

#include "freestanding.hh"
#include "mp1/mpsdk/retro_types.hh"
#include "mp1/rstl/string.hh"

class CStateManager;
class CInGameGuiManager;

enum EGameFlowState { InGame = 0, Paused, SamusDied, CinematicSkip };
enum class EArchMsgTarget { IOWinManager = 0, Game = 1 };
enum class EArchMsgType {
   RemoveIOWin = 0,
   CreateIOWin = 1,
   ChangeIOWinPriority = 2,
   RemoveAllIOWins = 3,
   TimerTick = 4,
   UserInput = 5,
   SetGameState = 6,
   ControllerStatus = 7,
   QuitGameplay = 8,
   FrameBegin = 10,
   FrameEnd = 11,
};

struct CArchitectureMessage {
   NO_INSTANTIATE(CArchitectureMessage);

   struct CArchMsgParam {
      uintptr_t const* const vtable;
      u8 val[0];
   };

   EArchMsgTarget target;
   EArchMsgType type;
   // technically a shared_ptr
   CArchMsgParam** param;

   template <typename T>
   T& get_param_val() {
      return *reinterpret_cast<T*>(&(*param)->val);
   }
};

class CMFGame {
protected:
   // from CIOWin
   uintptr_t const* const vtable;
   rstl::string name;

   // from CMFGame
   CStateManager* state_mgr;
   CInGameGuiManager* gui_mgr;
   EGameFlowState state;
   float cinematic_skip_time;
   u32 cmfgame_unk1;
   TUniqueId skipped_cinematic_cam_id;
   bool initialized : 1;
   bool samus_alive : 1;

public:
   NO_INSTANTIATE(CMFGame);

   int original_onmessage(CArchitectureMessage const* arch_msg, void* arch_queue) {
      return call_class_func<int, CArchitectureMessage const*, void*>(0x8002469c, this, arch_msg,
                                                                      arch_queue);
   }
   void original_draw() { call_class_func<void>(0x80024564, this); }
   bool is_initialized() const { return initialized; }
};
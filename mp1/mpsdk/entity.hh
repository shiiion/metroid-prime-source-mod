#pragma once

#include "freestanding.hh"
#include "mp1/mpsdk/entity_info.hh"
#include "mp1/mpsdk/retro_types.hh"
#include "mp1/mpsdk/script_object_support.hh"
#include "mp1/rstl/string.hh"
#include "mp1/rstl/vector.hh"
#include "util/func_caller.hh"

class IVisitor;
class CStateManager;

class CEntity {
public:
   NO_INSTANTIATE(CEntity);

   void accept(IVisitor& visitor) { call_vfunc<void, IVisitor&>(this, 1, visitor); }
   void pre_think(float dt, CStateManager& mgr) {
      call_vfunc<void, float, CStateManager&>(this, 2, dt, mgr);
   }
   void think(float dt, CStateManager& mgr) {
      call_vfunc<void, float, CStateManager&>(this, 3, dt, mgr);
   }
   void accept_script_msg(EScriptObjectMessage msg, TUniqueId id, CStateManager& mgr) {
      call_vfunc<void, EScriptObjectMessage, TUniqueId, CStateManager&>(this, 4, msg, id, mgr);
   }
   void set_active(bool active) { call_vfunc<void, bool>(this, 5, active); }

   bool get_active() const { return active; }
   void toggle_active() { active ^= 1; }
   bool is_in_graveyard() const { return in_graveyard; }
   bool is_scripting_blocked() const { return scripting_blocked; }
   bool is_in_use() const { return in_use; }

   TAreaId get_area_id() const { return in_use ? area_id : kInvalidAreaId; }
   TAreaId get_area_id_always() const { return area_id; }
   TUniqueId get_unique_id() const { return uid; }
   TEditorId get_editor_id() const { return editor_id; }
   rstl::vector<SConnection>& get_connection_list() { return connections; }
   const rstl::vector<SConnection>& get_connection_list() const { return connections; }
   rstl::string get_name() const { return name; }

   void send_script_msgs(EScriptObjectState state, CStateManager& mgr, EScriptObjectMessage msg) {
      call_class_func<void, EScriptObjectState, CStateManager&, EScriptObjectMessage>(
          0x800510C0, this, state, mgr, msg);
   }

protected:
   uintptr_t const* const vtable;
   TAreaId area_id;
   TUniqueId uid;
   TEditorId editor_id;
   rstl::string name;
   rstl::vector<SConnection> connections;
   bool active : 1;
   bool in_graveyard : 1;
   bool scripting_blocked : 1;
   bool in_use : 1;
};
#pragma once

#include "mp1/mpsdk/retro_types.hh"
#include "mp1/mpsdk/script_object_support.hh"
#include "mp1/rstl/vector.hh"

struct SConnection {
   EScriptObjectState state;
   EScriptObjectMessage msg;
   TEditorId object_id;
};

class CEntityInfo {
public:
   TAreaId area_id;
   rstl::vector<SConnection> connections;
   TEditorId editor_id;
};

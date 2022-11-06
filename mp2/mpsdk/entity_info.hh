#pragma once

#include "mp2/mpsdk/retro_types.hh"
#include "mp2/mpsdk/script_object_support.hh"
#include "mp2/rstl/vector.hh"

struct SConnection {
   EScriptObjectState state;
   EScriptObjectMessage msg;
   TEditorId object_id;
};

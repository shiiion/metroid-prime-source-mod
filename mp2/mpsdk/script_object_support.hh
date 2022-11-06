#pragma once

#include "freestanding.hh"

// These are dummy enums that will be filled as discovered/needed
// mp2 switched from raw values to FourCC (e.g. Active -> ACTV)

enum class EScriptObjectType {
    Unknown
};

enum class EScriptObjectState : uint32_t {
    Unknown
};

enum class EScriptObjectMessage : uint32_t {
    Unknown
};

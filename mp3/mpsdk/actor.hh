#pragma once

#include "mp3/mpsdk/entity.hh"
#include "util/r_math.hh"

class CActor : public CEntity {
public:
   mat34 transform; // 3c
   vec3 position; // 6c
   uint8_t cactor_unk0[0xdc]; // 78 -> 154

public:
   mat34 const& get_transform() const { return transform; }
   mat34& get_transform() { return transform; }
   vec3 const& get_position() const { return position; }
   vec3& get_position() { return position; }
   void set_position(vec3 const& pos) { position = pos; }
};

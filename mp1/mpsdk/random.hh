#pragma once

#include "freestanding.hh"
#include "util/func_caller.hh"

using CRandom16 = s32;

class CGlobalRandom {
   CRandom16& random;
   bool cglobalrandom_unk1;
   CGlobalRandom* prev_random;

public:
   CGlobalRandom(CRandom16& rnd) : random(rnd) {
      call_class_func<void, CRandom16&>(0x80312680, this, rnd);
   }
   ~CGlobalRandom() { call_class_func<void, int>(0x80312604, this, -1); }
};
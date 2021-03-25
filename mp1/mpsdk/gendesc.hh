#pragma once

#include "freestanding.hh"
#include "mp1/mpsdk/r_math.hh"
#include "mp1/mpsdk/retro_types.hh"
#include "util/func_caller.hh"

// HACK: Could handle all cases, but not worth the effort
template <typename T1>
struct TElement1 {
   bool get_value(int frame, T1& val_out) const {
      return call_vfunc<bool, int, T1&>(this, 1, frame, val_out);
   }
};
template <typename T1, typename T2>
struct TElement2 {
   bool get_value(int frame, T1& val_out1, T2& val_out2) const {
      return call_vfunc<bool, int, T1&, T2&>(this, 1, frame, val_out1, val_out2);
   }
};

struct UVVal {
    float x_min, y_min, x_max, y_max;
};

class CModel;
class CSpawnSystemKeyframeData;

struct CGenDescription {
   NO_INSTANTIATE(CGenDescription);

   TElement1<int>* PSLT;
   TElement1<int>* PSWT;
   TElement1<float>* PSTS;
   TElement1<vec3>* POFS;
   TElement1<int>* SEED;
   TElement1<float>* LENG;
   TElement1<float>* WIDT;
   TElement1<int>* MAXP;
   TElement1<float>* GRTE;
   TElement1<CColor>* COLR;
   TElement1<int>* LTME;
   TElement2<vec3, vec3>* EMTR;
   bool LINE : 1;
   bool FXLL : 1;
   bool AAPH : 1;
   bool ZBUF : 1;
   bool SORT : 1;
   bool LIT_ : 1;
   bool ORNT : 1;
   bool RSOP : 1;
   bool MBLR : 1;
   bool PMAB : 1;
   bool PMUS : 1;
   bool PMOO : 1;
   bool VMD1 : 1;
   bool VMD2 : 1;
   bool VMD3 : 1;
   bool VMD4 : 1;
   bool CIND : 1;
   bool OPTS : 1;
   TElement1<int>* MBSP;
   TElement1<float>* SIZE;
   TElement1<float>* ROTA;
   TElement1<UVVal>* TEXR;
   TElement1<UVVal>* TIND;
   u8 padding__PMDL[0x10];
   TElement1<vec3>* PMOP;
   TElement1<vec3>* PMRT;
   TElement1<vec3>* PMSC;
   TElement1<CColor>* PMCL;
   TElement2<vec3, vec3>* VEL1;
   TElement2<vec3, vec3>* VEL2;
   TElement2<vec3, vec3>* VEL3;
   TElement2<vec3, vec3>* VEL4;
   u8 padding__ICTS[0x10];
   TElement1<int>* NCSY;
   TElement1<int>* CSSD;
   u8 padding__IDTS[0x10];
   TElement1<int>* NDSY;
   u8 padding__IITS[0x10];
   TElement1<int>* PISY;
   TElement1<int>* SISY;
   CSpawnSystemKeyframeData* KSSM;
   u8 padding__SSWH[0x10];
   TElement1<int>* SSSD;
   TElement1<vec3>* SSPO;
   u8 padding__SELC[0xc];
   TElement1<int>* SESD;
   TElement1<vec3>* SEPO;
   TElement1<int>* LTYP;
   TElement1<CColor>* LCLR;
   TElement1<float>* LINT;
   TElement1<vec3>* LOFF;
   TElement1<vec3>* LDIR;
   TElement1<int>* LFOT;
   TElement1<float>* LFOR;
   TElement1<float>* LSLA;
   TElement1<float>* ADV1;
   TElement1<float>* ADV2;
   TElement1<float>* ADV3;
   TElement1<float>* ADV4;
   TElement1<float>* ADV5;
   TElement1<float>* ADV6;
   TElement1<float>* ADV7;
   TElement1<float>* ADV8;
};
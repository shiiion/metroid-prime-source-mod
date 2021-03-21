#include "mp1/mpsdk/os.hh"

#include "util/func_caller.hh"

u64 os_get_time() { return call_func<u64>(0x803853a8); }
float compute_elapsed(u64 start, u64 end) {
   const u64 delta = end - start;
   float f_delta = call_func<float, u64>(0x80389f64, delta);
   return f_delta * *reinterpret_cast<float*>(0x8059fd40);
}
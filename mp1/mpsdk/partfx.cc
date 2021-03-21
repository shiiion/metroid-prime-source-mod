#include "mp1/mpsdk/partfx.hh"

#include "util/func_caller.hh"

void CParticleGen::destroy_and_free() {
    call_vfunc<void, int>(this, 0, 1);
}

void CElementGen::reset_generator() {
    // CElementGen::DestroyParticles
    call_vfunc<void>(this, 25);
    for (CParticleGen* child : active_children) {
        child->destroy_and_free();
    }
    active_children.clear();
    cur_frame = 0;
    cur_seconds = 0.0;
    prev_frame = -1;
    active_particle_count = 0;
    warmed_up = false;
}
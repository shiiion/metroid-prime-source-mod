#include "freestanding.hh"

extern "C" {
char debug_output[2048];

float crouch_height = 0.5f;
}
#define sprintf(str, fmt, ...) \
  ((int (*)(char *, const char *, ...))0x802b04c4)((str), (fmt), __VA_ARGS__)

using u32 = uint32_t;

inline float sqrt(float x) {
  using sqrt_fn = float (*)(float);
  return ((sqrt_fn)0x803825E8)(x);
}

struct vec3 {
  vec3() : vec3(0, 0, 0) {}
  vec3(float x, float y, float z) : x(x), y(y), z(z) {}

  union {
    float arr[3];
    struct {
      float x, y, z;
    };
  };

  vec3 operator*(float s) const { return vec3(x * s, y * s, z * s); }

  vec3 operator+(vec3 const& rhs) const { return vec3(x + rhs.x, y + rhs.y, z + rhs.z); }

  vec3 operator-(vec3 const& rhs) const { return *this + -rhs; }

  vec3 operator-() const { return vec3(-x, -y, -z); }

  vec3& operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }

  vec3& operator+=(const vec3& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  vec3& operator-=(const vec3& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  float dot(const vec3& other) const { return x * other.x + y * other.y + z * other.z; }

  float mag_sq() const { return dot(*this); }

  float mag() const { return sqrt(mag_sq()); }

  void normalize() {
    float m = 1.f / mag();
    *this *= m;
  }

  vec3 normalized() const {
    float m = 1.f / mag();
    return *this * m;
  }
};

struct Transform {
  float m[3][4];

  vec3 right() const { return vec3(m[0][0], m[1][0], m[2][0]); }

  vec3 fwd() const { return vec3(m[0][1], m[1][1], m[2][1]); }

  vec3 up() const { return vec3(m[0][2], m[1][2], m[2][2]); }

  vec3 loc() const { return vec3(m[0][3], m[1][3], m[2][3]); }

  void set_loc(vec3 const& v) {
    m[0][3] = v.x;
    m[1][3] = v.y;
    m[2][3] = v.z;
  }
};

template <typename T, uint32_t _Max>
struct reserved_vec {
  uint32_t size = 0;
  T storage[_Max];
};

struct matfilter {
  uint64_t include;
  uint64_t exclude;
  uint32_t type;
};

struct aabb {
  vec3 min;
  vec3 max;
};

template <typename... Ts>
constexpr uint64_t cons_matlist(Ts... types) {
   return uint64_t{0} | ((uint64_t{1} << static_cast<uint32_t>(types)) | ...);
}

bool detect_collision_boolean(void* mgr, void* prim, Transform const* xf, matfilter const& filter, reserved_vec<uint16_t, 1024>const& near_list) {
  using dcb_fn = bool (*)(void*, void*, Transform const*, matfilter const&, reserved_vec<uint16_t, 1024>const&);
  return ((dcb_fn)0x800a3134)(mgr, prim, xf, filter, near_list);
}

void build_collider_list(void* mgr, reserved_vec<uint16_t, 1024>& near, void* actor, aabb const& bounds) {
  using bcl_fn = void (*)(void*, reserved_vec<uint16_t, 1024>&, void*, aabb const&);
  ((bcl_fn)0x8023e918)(mgr, near, actor, bounds);
}

void* get_player_prim(char* player) {
  return player + 0x228;
}

bool collision_detect(char* player, void* mgr) {
  reserved_vec<uint16_t, 1024> near_list;
  aabb player_bb = *(aabb*)(player + 0x238);
  const Transform& player_xf = *(Transform*)(player + 0x20);
  player_bb.min += player_xf.loc();
  player_bb.max += player_xf.loc();
  build_collider_list(mgr, near_list, player, player_bb);
  matfilter filter;
  filter.include = cons_matlist(0x3b);
  filter.exclude = 0;
  filter.type = 1;
  bool detected = detect_collision_boolean(mgr, get_player_prim(player), (Transform const*)(player + 0x20), filter, near_list);
  return detected;
}

void* get_mapping(void* cplayer) {
   using get_mapping_fn = void* (*)(void*);
   return ((get_mapping_fn)0x8014EC94)(cplayer);
} 

float get_analog_input(void* player, int command, void* input, int unk) {
  using get_analog_input_fn = float (*)(void*, void*, int, void*, int);
  return ((get_analog_input_fn)0x8006fe1c)(reinterpret_cast<uint8_t*>(player) + 0x13bc, get_mapping(player), command, input, unk);
}

bool get_digital_input(void* player, int command, void* input, int unk) {
  using get_digital_input_fn = bool (*)(void*, void*, int, void*, int);
  return ((get_digital_input_fn)0x80070424)(reinterpret_cast<uint8_t*>(player) + 0x13bc, get_mapping(player), command, input, unk);
}

bool get_press_input(void* player, int command, void* input, int unk) {
  using get_press_input_fn = bool (*)(void*, void*, int, void*, int);
  return ((get_press_input_fn)0x800706BC)(reinterpret_cast<uint8_t*>(player) + 0x13bc, get_mapping(player), command, input, unk);
}

float get_gravity(void* player) {
  using get_gravity_fn = float (*)(void*);
  return ((get_gravity_fn)0x8015cf98)(player);
}

void set_move_state(void* player, int state, void* mgr) {
  using set_move_state_fn = void (*)(void*, int, void*);
  return ((set_move_state_fn)0x8015FB78)(player, state, mgr);
}

void set_velocity_wr(void* player, const vec3& vel) {
  using set_velocity_wr_fn = void (*)(void*, const vec3&);
  return ((set_velocity_wr_fn)0x80135930)(player, vel);
}

float max(float f1, float f2) {
  return f1 > f2 ? f1 : f2;
}

int get_suit_num() {
  char* state_mgr = (char*)0x804e72e8;
  char* player_state = *(char**)(state_mgr + 0x1504);
  return *(int*)(player_state + 0x50);
}

bool has_powerup(int idx) {
  char* state_mgr = (char*)0x804e72e8;
  char* player_state = *(char**)(state_mgr + 0x1504);
  return ((int*)(player_state + 0x58))[idx * 3 + 1] != 0;
}

int get_surface_restraint(char* player) {
  return *(int*)(player + 0x330);
}

bool in_morphball(char* player) {
  return *(int*)(player + 0x378) != 0; 
}

void set_gravity(float gravity) {
  char* player_tweak = **((char***)0x805cb250);

  *(float*)(player_tweak + 0x100) = gravity;
}

void set_gravboost_force(float force) {
  char* player_tweak = **((char***)0x805cb250);

  *(float*)(player_tweak + 0x164) = force;
}

void set_screwattack_leniency_height(float height) {
  char* pup_tweak = **((char***)0x805cb23c);
  *(float*)(pup_tweak + 0x21c) = height;
}

void start_screw_attack(char* player, int unk) {
  using start_screw_attack_fn = void (*)(void*, int);
  return ((start_screw_attack_fn)0x80162f88)(player, unk);
}

void start_grav_boost(char* player) {
  using start_grav_boost_fn = void (*)(void*, u32);
  return ((start_grav_boost_fn)0x801638a8)(player, 0x804e72e8);
}

void stop_grav_boost(char* player) {
  using stop_grav_boost_fn = void (*)(void*, u32);
  return ((stop_grav_boost_fn)0x80163acc)(player, 0x804e72e8);
}


Transform& get_transform(char* player) {
  return *(Transform*)(player + 0x20);
}

aabb& get_collision_bounds(char* player) {
  return *(aabb*)(player + 0x238);
}

struct raycast_result {
  float dist;
  vec3 point;
  float plane[4];
  uint64_t materials;
  bool valid;
};

raycast_result ray_static_intersection(void* mgr, vec3 const& pt, vec3 const& dir, float dist, matfilter const& filter) {
  using rsi_fn = raycast_result (*)(void*, vec3 const&, vec3 const&, float, matfilter const&);
  return ((rsi_fn)0x800a2d64)(mgr, pt, dir, dist, filter);
}

bool update_crouch(char* player, bool cur_crouch_button, int move_state, void* mgr) {
  static bool crouch_button_state = false;
  static bool uncrouch_requested = false;
  static bool is_crouching = false;

  const auto do_crouch = [](char* player) {
    get_collision_bounds(player).max.z = crouch_height;
    *(float*)(player + 0x36c) = crouch_height;
  };
  const auto do_uncrouch = [](char* player) {
    get_collision_bounds(player).max.z = 2.7f;
    *(float*)(player + 0x36c) = 2.7f;
  };
  
  if (crouch_button_state != cur_crouch_button) {
    if (cur_crouch_button && !uncrouch_requested) {
      do_crouch(player);
      is_crouching = true;
    } else {
      uncrouch_requested = true;
      do_uncrouch(player);
      if (collision_detect(player, mgr)) {
        do_crouch(player);
      } else {
        uncrouch_requested = false;
        is_crouching = false;
      }
    }
  } else if (!cur_crouch_button && uncrouch_requested) {
    do_uncrouch(player);
    if (collision_detect(player, mgr)) {
      do_crouch(player);
    } else {
      uncrouch_requested = false;
      is_crouching = false;
    }
  }

  crouch_button_state = cur_crouch_button;
  return is_crouching;
}

extern "C" {

int shutdown_signal = 0;

float jump_restraint_table[8] = {1.f, 1.f, 1.f, 1.f, 1.f, 0.3f, 0.3f, 1.f};
float accel_restraint_table[8] = {1.f, 1.f, 1.f, 1.f, 1.f, 0.3f, 0.3f, 0.3f};
// how fast can turning happen?
float airaccel_restraint_table[8] = {1.f, 1.f, 1.f, 1.f, 1.f, 0.01f, 0.1f, 1.f};
// how much speed is gained from turning?
float airmove_clamp_table[8] = {1.f, 1.f, 1.f, 1.f, 1.f, 0.5f, 0.5f, 1.f};

// Multiplier on air acceleration (primarily impacts how quickly turns can be done)
float airaccelerate_mul = 500.f;
// Multiplier on walking acceleration
float accelerate_mul = 16.5f;
// Maximum walking velocity (based on XY)
float max_walk_speed = 15.f;
// Multiplier on friction
float friction_mul = 10.4f;
// Maximum speed gain per tick from airaccel
float airaccelerate_wishspeed_clamp = 1.2f;
// Z component of velocity on jumping
float jump_impulse = 20.f;
// Multiplier on normal player gravity
float gravity_mul = 1.f;
// Multiplier on input values, transforms input space from [0, 1] -> [0, wishspeed] 
float input_wishspeed = 15.f;
// If speed is less than this, then friction is applied based on this value (aka, the "stop speed")
float stop_speed = 6.f;
// Number of ticks after moving to falling state to get a double jump
int leniency_ticks = 5;
// Maximum drop for screw attack
float screwattack_max_drop = 20.f;
// Additional height to add to the screw attack start
float screwattack_extra_starting_height = 2.f;

void release_mod() {}

float lookup_jump_mult(char* player, int restraint) {
  if ((restraint == 5 || restraint == 6) && (*(float*)(player + 0x1220) < 3.f)) {
    return jump_restraint_table[0];
  }
  return jump_restraint_table[restraint];
}

float* get_player_gunswitch_time(char* player) {
  return (float*)(*(char**)(player + 0xea8) + 0x4c4);
}

// TODO: make this code less source-engine like (looks AWFUL!!)
void hooked_computemove(char* player, void* input, void* mgr, float dt) {
  if (in_morphball(player)) {
    set_gravity(-35.f);
  } else {
    set_gravity(-51.f);
  }
  *get_player_gunswitch_time(player) = 0.f;

  int move_state = *(int*)(player + 0x2c4);
  bool crouch_hold = *(reinterpret_cast<char*>(input) + 0x10c) == 0x01;
  update_crouch(player, crouch_hold, move_state, mgr);
  set_gravboost_force(13000.f);
  set_screwattack_leniency_height(screwattack_max_drop);
  static int num_jumps = 0;
  static int num_ticks_in_air = 0;
  static bool is_gravboosting = false;
  bool has_doublejump = has_powerup(24);
  bool has_screwattack = false; //has_powerup(27);
  bool has_gravboost = has_powerup(25);
  
  if (move_state != 0) { 
    num_ticks_in_air++;
  } else {
    num_ticks_in_air = 0;
    num_jumps = 0;
  }
  if (num_ticks_in_air > leniency_ticks && (num_jumps == 0)) {
    num_jumps = 1;
  }

  int restraint = get_surface_restraint(player);
  vec3 vel = *(vec3*)(player + 0x1a0);
  float half_grav = get_gravity(player) * 0.5f * gravity_mul * dt;


  vel += vec3(0, 0, half_grav);
  set_velocity_wr(player, vel);

  bool jumping = get_digital_input(player, 11, input, 0);
  bool jump_this_tick = get_press_input(player, 11, input, 0);
  float water_depth = *(float*)(player + 0x1220);
  if (is_gravboosting && !jumping) {
    stop_grav_boost(player);
    is_gravboosting = false;
  }

  if (jumping && num_jumps == 0) {
    vel.z = jump_impulse * lookup_jump_mult(player, restraint);
    vel += vec3(0, 0, half_grav);
    set_move_state(player, 1, mgr);
    set_velocity_wr(player, vel);
    num_jumps = 1;
    return;
  }
  else if (jump_this_tick && move_state != 0 && (num_jumps == 1) && has_doublejump) {
    num_jumps = 2;
    vel.z = jump_impulse * lookup_jump_mult(player, restraint);
    vel += vec3(0, 0, half_grav);
    set_move_state(player, 1, mgr);
    set_velocity_wr(player, vel);
    *(float*)(player + 0x32c) = *(float*)(player + 0x58) + screwattack_extra_starting_height;
    return;
  }
  else if (has_screwattack && jump_this_tick && move_state != 0 && (num_jumps == 2) && (water_depth < 1.25f)) {
    start_screw_attack(player, 1);
    num_jumps++;
    return;
  }
  else if (has_gravboost && jump_this_tick && (num_jumps == 2)) {
    start_grav_boost(player);
    num_jumps++;
    is_gravboosting = true;
    return;
  }
  const Transform& player_xf = *(Transform*)(player + 0x20);
  if (move_state != 0) {
    vec3 forward, right;
    forward = player_xf.fwd();
    right = player_xf.right();

    forward.z = right.z = 0;
    forward.normalize();
    right.normalize();

    float fmove, smove, wishspd_clamp;
    fmove = get_analog_input(player, 1, input, 0) - get_analog_input(player, 2, input, 0);
    smove = get_analog_input(player, 6, input, 0) - get_analog_input(player, 5, input, 0);

    vec3 wishvel = forward * (fmove * input_wishspeed) + right * (smove * input_wishspeed);
    wishvel.z = 0;

    float wishspeed = wishvel.mag();
    vec3 wishdir = wishvel.normalized();
    if (wishspeed == 0.f) {
      wishdir = forward;
    }

    float airaccel = airaccelerate_mul * airaccel_restraint_table[restraint];
    const float max_wishspeed = airaccelerate_wishspeed_clamp * airmove_clamp_table[restraint];
    wishspd_clamp = wishspeed;
    if (wishspeed > max_wishspeed) {
      wishspd_clamp = max_wishspeed;
    }
    float currentspeed = vel.dot(wishdir);
    float addspeed = wishspd_clamp - currentspeed;
    if (addspeed <= 0) {
      goto end;
    }
    float accelspeed = airaccel * wishspeed * dt;
    if (accelspeed > addspeed) {
      accelspeed = addspeed;
    }

    vel += wishdir * accelspeed;
  } else {
    vel.z = 0;
    set_velocity_wr(player, vel);
    {  // friction
      float speed = vel.mag();
      if (speed < 0.1f) goto frictionend;

      float drop = 0;
      const float friction = friction_mul;
      float control = speed < stop_speed ? stop_speed : speed;
      drop += control * friction * dt;
      float newspeed = speed - drop;
      if (newspeed < 0) newspeed = 0;
      if (newspeed != speed) {
        newspeed /= speed;
        vel = vel * newspeed;
      }
    }
  frictionend:
    vec3 forward, right;
    forward = player_xf.fwd();
    right = player_xf.right();

    forward.z = right.z = 0;

    forward.normalize();
    right.normalize();

    float fmove, smove;
    
    fmove = get_analog_input(player, 1, input, 0) - get_analog_input(player, 2, input, 0);
    smove = get_analog_input(player, 6, input, 0) - get_analog_input(player, 5, input, 0);

    vec3 wishvel = (forward * (fmove * input_wishspeed)) + (right * (smove * input_wishspeed));
    wishvel.z = 0;

    float wishspeed = wishvel.mag();
    vec3 wishdir = wishvel.normalized();
    if (wishspeed == 0.f) {
      if (vel.mag_sq() == 0.f) {
        wishdir = forward;
      } else {
        wishdir = vel.normalized();
      }
    }

    vel.z = 0;

    {  // accelerate
      float currentspeed = vel.dot(wishdir);
      float addspeed = wishspeed - currentspeed;

      if (addspeed <= 0) goto accelerateend;

      float accelspeed = (accelerate_mul * accel_restraint_table[restraint]) * dt * max(max_walk_speed, wishspeed);

      if (accelspeed > addspeed) accelspeed = addspeed;

      vel = vel + wishdir * accelspeed;
    }
  accelerateend:
    vel.z = 0;

    if (vel.mag_sq() > max_walk_speed * max_walk_speed) {
      vel = vel * (max_walk_speed / vel.mag());
    }

    set_velocity_wr(player, vel);
  }
  end:
  vel += vec3(0, 0, half_grav);
  set_velocity_wr(player, vel);

}
}

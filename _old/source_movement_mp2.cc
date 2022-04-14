#include "freestanding.hh"

using u32 = uint32_t;

inline float sqrt(float x) {
  using sqrt_fn = float (*)(float);
  return ((sqrt_fn)0x8001D678)(x);
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
};

float get_analog_input(void* player_plus_13d0, int command, void* input) {
  using get_analog_input_fn = float (*)(void*, int, void*, int);
  return ((get_analog_input_fn)0x80009D18)(player_plus_13d0, command, input, 0);
}

bool get_digital_input(void* player_plus_13d0, int command, void* input) {
  using get_digital_input_fn = bool (*)(void*, int, void*, int);
  return ((get_digital_input_fn)0x80009C84)(player_plus_13d0, command, input, 0);
}

bool get_press_input(void* player_plus_13d0, int command, void* input) {
  using get_press_input_fn = bool (*)(void*, int, void*, int);
  return ((get_press_input_fn)0x80009BF0)(player_plus_13d0, command, input, 0);
}

float get_gravity(void* player) {
  using get_gravity_fn = float (*)(void*);
  return ((get_gravity_fn)0x80189B38)(player);
}

void set_move_state(void* player, int state, void* mgr) {
  using set_move_state_fn = void (*)(void*, int, void*);
  return ((set_move_state_fn)0x80187370)(player, state, mgr);
}

void set_velocity_wr(void* player, const vec3& vel) {
  using set_velocity_wr_fn = void (*)(void*, const vec3&);
  return ((set_velocity_wr_fn)0x800EA404)(player, vel);
}

float max(float f1, float f2) {
  return f1 > f2 ? f1 : f2;
}

int get_suit_num() {
  char* state_mgr = (char*)0x803db6e0;
  char* player_state = *(char**)(state_mgr + 0x150c);
  return *(int*)(player_state + 0x54);
}

bool has_powerup(int idx) {
  char* state_mgr = (char*)0x803db6e0;
  char* player_state = *(char**)(state_mgr + 0x150c);
  return ((int*)(player_state + 0x5c))[idx * 3 + 1] != 0;
}

int get_surface_restraint(char* player) {
  return *(int*)(player + 0x344);
}

bool in_morphball(char* player) {
  return *(int*)(player + 0x38c) != 0; 
}

void set_gravity(float gravity) {
  char* player_tweak = **((char***)0x80418F44);

  *(float*)(player_tweak + 0x104) = gravity;
}

void set_gravboost_force(float force) {
  char* player_tweak = **((char***)0x80418F44);

  *(float*)(player_tweak + 0x168) = force;
}

void set_screwattack_leniency_height(float height) {
  char* pup_tweak = **((char***)0x80418F2C);
  *(float*)(pup_tweak + 0x220) = height;
}

void start_screw_attack(char* player, int unk) {
  using start_screw_attack_fn = void (*)(void*, int);
  return ((start_screw_attack_fn)0x80184294)(player, unk);
}

void start_grav_boost(char* player) {
  using start_grav_boost_fn = void (*)(void*, u32);
  return ((start_grav_boost_fn)0x8018381C)(player, 0x803db6e0);
}

void stop_grav_boost(char* player) {
  using stop_grav_boost_fn = void (*)(void*, u32);
  return ((stop_grav_boost_fn)0x80183648)(player, 0x803db6e0);
}

#define sprintf(str, fmt, ...) \
  ((int (*)(char *, const char *, ...))0x8034BEEC)((str), (fmt), __VA_ARGS__)


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

char debug_output[2048];

float lookup_jump_mult(char* player, int restraint) {
  if ((restraint == 5 || restraint == 6) && (*(float*)(player + 0x1248) < 3.f)) {
    return jump_restraint_table[0];
  }
  return jump_restraint_table[restraint];
}

// TODO: make this code less source-engine like (looks AWFUL!!)
void compute_walk_move(char* player, void* input, void* mgr, float dt) {
  if (in_morphball(player)) {
    set_gravity(-35.f);
  } else {
    set_gravity(-51.f);
  }
  set_gravboost_force(13000.f);
  set_screwattack_leniency_height(screwattack_max_drop);
  static int num_jumps = 0;
  static int num_ticks_in_air = 0;
  static bool is_gravboosting = false;
  bool has_doublejump = has_powerup(24);
  bool has_screwattack = has_powerup(27);
  bool has_gravboost = has_powerup(25);
  int move_state = *(int*)(player + 0x2d0);
  
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
  vec3 vel = *(vec3*)(player + 0x1a8);
  float half_grav = get_gravity(player) * 0.5f * gravity_mul * dt;
  int unk_input = get_press_input(player+0x13d0, 0x4a, input);
  int unk_input2 = get_press_input(player+0x13d0, 0x4b, input);


  vel += vec3(0, 0, half_grav);
  set_velocity_wr(player, vel);

  bool jumping = get_digital_input(player + 0x13d0, 11, input);
  bool jump_this_tick = get_press_input(player + 0x13d0, 11, input);
  float water_depth = *(float*)(player + 0x1248);
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
    *(float*)(player + 0x340) = *(float*)(player + 0x5c) + screwattack_extra_starting_height;
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
  const Transform& player_xf = *(Transform*)(player + 0x24);
  if (move_state != 0) {
    vec3 forward, right;
    forward = player_xf.fwd();
    right = player_xf.right();

    forward.z = right.z = 0;
    forward.normalize();
    right.normalize();

    float fmove, smove, wishspd_clamp;
    fmove = get_analog_input(player + 0x13d0, 1, input) - get_analog_input(player + 0x13d0, 2, input);
    smove = get_analog_input(player + 0x13d0, 8, input) - get_analog_input(player + 0x13d0, 7, input);

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
    
    fmove = get_analog_input(player + 0x13d0, 1, input) - get_analog_input(player + 0x13d0, 2, input);
    smove = get_analog_input(player + 0x13d0, 8, input) - get_analog_input(player + 0x13d0, 7, input);

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

#pragma once

#include "freestanding.hh"

float sin(float x);
float cos(float x);
float tan(float x);
float asin(float x);
float acos(float x);
float atan2(float x);
float sqrt(float x);
float floor(float x);
float sign(float x);
float fabs(float x);

double labs(double x);

template <typename T>
constexpr T max(T a, T b) {
   return (a > b ? a : b);
}
template <typename T>
constexpr T min(T a, T b) {
   return (a < b ? a : b);
}
template <typename T>
constexpr T clamp(T val, T min, T max) {
   return min(max(val, min), max);
}

struct vec3 {
   union {
      struct {
         float x, y, z;
      };
      float arr[3];
   };
   vec3(float x = 0.f, float y = 0.f, float z = 0.f) : x(x), y(y), z(z) {}

   vec3 operator*(float scalar) const { return vec3(x * scalar, y * scalar, z * scalar); }
   vec3 operator+(const vec3& rhs) const { return vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
   vec3 operator-(const vec3& rhs) const { return vec3(x - rhs.x, y - rhs.y, z - rhs.z); }
   vec3 operator-() const { return vec3(-x, -y, -z); }
   constexpr float operator[](ptrdiff_t idx) const { return arr[idx]; }

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
   vec3& operator*=(float scalar) {
      x *= scalar;
      y *= scalar;
      z *= scalar;
      return *this;
   }

   inline float dot(vec3 const& other) const { return x * other.x + y * other.y + z * other.z; }
   inline float magnitude_sqr() const { return dot(*this); }
   float magnitude() const;
   float xy_magnitude() const;
   vec3 normalized() const;
   void normalize();
};

struct vec4 {
   float v[4];
};

struct mat34 {
   float m[3][4];

   mat34();
   mat34(mat34 const& other);

   vec3 right() const { return vec3(m[0][0], m[1][0], m[2][0]); }
   vec3 fwd() const { return vec3(m[0][1], m[1][1], m[2][1]); }
   vec3 up() const { return vec3(m[0][2], m[1][2], m[2][2]); }
   vec3 loc() const { return vec3(m[0][3], m[1][3], m[2][3]); }
   void set_loc(const vec3& l) {
      m[0][3] = l.x;
      m[1][3] = l.y;
      m[2][3] = l.z;
   }

   mat34& operator=(mat34 const& rhs);
   vec3 operator*(vec3 const& rhs) const;
   mat34 operator*(mat34 const& rhs) const;

   static mat34 scale(float x, float y, float z);
   static mat34 translate(float x, float y, float z);
};

struct mat3 {
   float m[3][3];
};

struct aabox {
   vec3 mins;
   vec3 maxes;

   void move(vec3 const& v_move) {
      mins += v_move;
      maxes += v_move;
   }
};

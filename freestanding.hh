#pragma once

#define UINT8_MAX 0xffu
#define UINT16_MAX 0xffffu
#define UINT32_MAX 0xffffffffu
#define UINT64_MAX 0xffffffffffffffffu

#define INT8_MAX 0x7f
#define INT8_MIN 0x80
#define INT16_MAX 0x7fff
#define INT16_MIN 0x8000
#define INT32_MAX 0x7fffffff
#define INT32_MIN 0x80000000
#define INT64_MAX 0x7fffffffffffffff
#define INT64_MIN 0x8000000000000000
#define FLT_MAX 3.40282347E+38F

extern "C" {
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

typedef uint32_t size_t;
typedef uint32_t uintptr_t;

typedef int32_t ssize_t;
typedef int32_t ptrdiff_t;

void* memcpy(void* dst, const void* src, size_t len);
void* memmove(void* dst, const void* src, size_t len);
void* memset(void* dst, int val, size_t len);
int memcmp(const void* c1, const void* c2, size_t len);
int strlen(const char* s);
void strcpy(char* dst, const char* src);
void strcat(char* dst, const char* src);
bool strcmp(const char* s1, const char* s2);

void mod_start();
}

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;

#define NO_INSTANTIATE(c) \
    c() = delete; \
    c(c const&) = delete; \
    c(c&&) = delete;

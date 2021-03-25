#include "freestanding.hh"

void* memcpy(void* dst, const void* src, size_t len) {
   uint8_t* dst_byte = (uint8_t*)dst;
   uint8_t* src_byte = (uint8_t*)src;
   for (size_t i = 0; i < len; i++) {
      *dst_byte++ = *src_byte++;
   }
   return dst;
}

void* memmove(void* dst, const void* src, size_t len) {
   if (dst == src) {
      return dst;
   } else if (dst < src) {
      return memcpy(dst, src, len);
   } else {
      uint8_t* dst_byte = ((uint8_t*)dst) + len - 1;
      uint8_t* src_byte = ((uint8_t*)src) + len - 1;
      for (size_t i = 0; i < len; i++) {
         *dst_byte++ = *src_byte++;
      }
      return dst;
   }
}

void* memset(void* dst, int val, size_t len) {
   uint8_t* dst_byte = (uint8_t*)dst;
   for (size_t i = 0; i < len; i++) {
      *dst_byte++ = (uint8_t)val;
   }
   return dst;
}

int memcmp(const void* c1, const void* c2, size_t len) {
   uint8_t* c1_byte = (uint8_t*)c1;
   uint8_t* c2_byte = (uint8_t*)c2;

   for (size_t i = 0; i < len; i++) {
      if (*c1_byte != *c2_byte) {
         return *c1_byte < *c2_byte ? -1 : 1;
      }
      c1_byte++;
      c2_byte++;
   }
   return 0;
}

int strlen(const char* s) {
   const char* sp = s;
   while (*sp++)
      ;
   return sp - s - 1;
}

void strcpy(char* dst, const char* src) {
   while (*src) {
      *dst++ = *src++;
   }
   *dst = *src;
}

void strcat(char* dst, const char* src) {
   int start_index = strlen(dst);
   strcpy(dst + start_index, src);
}

bool strcmp(const char* s1, const char* s2) {
   while (*s1 && *s2 && (*s1 == *s2)) {
      s1++;
      s2++;
   }
   return *s1 == *s2;
}


void operator delete(void*, unsigned int) {}
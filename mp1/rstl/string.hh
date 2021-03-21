#pragma once

#include "freestanding.hh"
#include "util/func_caller.hh"

namespace rstl {

template <typename _CharT>
class _string_base {
public:
   using char_type = _CharT;

protected:
   friend class allocated_string;
   struct COWData {
      uint32_t capacity;
      uint32_t ref_count;
      char_type const* data[];
   };

   char_type const* _data;
   COWData* _cow_data;
   size_t _size;
   u8 padding[0x4];

   _string_base(char_type const* data, COWData* cow_data, size_t size)
       : _data(data), _cow_data(cow_data), _size(size) {}

public:
   class const_iterator {
   protected:
      char_type const* _it;

   public:
      explicit const_iterator(char_type const* it) : _it(it) {}
      char_type const& operator*() const { return *_it; }
      char_type const* operator->() const { return _it; }
      const_iterator& operator++() {
         ++_it;
         return *this;
      }
      const_iterator& operator--() {
         --_it;
         return *this;
      }
      const_iterator operator++(int) {
         auto ret = *this;
         ++_it;
         return ret;
      }
      const_iterator operator--(int) {
         auto ret = *this;
         --_it;
         return ret;
      }
      bool operator!=(const_iterator const& other) const { return _it != other._it; }
      bool operator==(const_iterator const& other) const { return _it == other._it; }
      const_iterator operator+(ptrdiff_t i) const { return const_iterator(_it + i); }
      const_iterator operator-(ptrdiff_t i) const { return const_iterator(_it - i); }
      const_iterator& operator+=(ptrdiff_t i) {
         _it += i;
         return *this;
      }
      const_iterator& operator-=(ptrdiff_t i) {
         _it -= i;
         return *this;
      }
      ptrdiff_t operator-(const_iterator const& rhs) const { return _it - rhs._it; }
      bool operator>(const_iterator const& rhs) const { return _it > rhs._it; }
      bool operator<(const_iterator const& rhs) const { return _it < rhs._it; }
      bool operator>=(const_iterator const& rhs) const { return _it >= rhs._it; }
      bool operator<=(const_iterator const& rhs) const { return _it <= rhs._it; }
      char_type const& operator[](ptrdiff_t i) const { return _it[i]; }
   };

   _string_base(char_type const* str, int len = -1) : _data(str), _cow_data(nullptr) {
      if (len == -1) {
         _size = static_cast<size_t>(strlen(str));
      } else {
         _size = len;
      }
   }
   _string_base() : _string_base("", 0) {}

   char_type operator[](ssize_t idx) const { return _data[idx]; }

   const_iterator begin() const { return const_iterator(_data); }
   const_iterator end() const { return const_iterator(_data + _size); }

   size_t size() const { return _size; }
   char_type const* data() const { return _data; }
};

// Try to keep allocated_strings as allocated!!
class allocated_string : public _string_base<char> {
public:
   using base = _string_base<char>;
   using const_iterator = typename base::const_iterator;
   using char_type = typename base::char_type;

private:
   void internal_dereference();

public:
   allocated_string(char_type const* str, int len = -1);
   allocated_string(base const& str);
   allocated_string() : base() {}

   void append(char_type const* str, int len = -1);
   void append(allocated_string const& str);
   void append(base const& str);
   allocated_string& operator=(char_type const* rhs);
   allocated_string& operator=(allocated_string const& rhs);
   allocated_string& operator=(base const& rhs);

   allocated_string substr(int beg, int end) const;

   ~allocated_string() { internal_dereference(); }
};

using string_base = _string_base<char>;
using string = allocated_string;

allocated_string operator+(string_base const& lhs, string_base const& rhs);
allocated_string operator+(string_base const& lhs, string_base::char_type const* rhs);

}  // namespace rstl
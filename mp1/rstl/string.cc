#include "mp1/rstl/string.hh"

namespace rstl {

void allocated_string::internal_dereference() {
   // Forward to basic_string::internal_dereference
   call_class_func<void>(0x8033dae0, this);
}

allocated_string::allocated_string(allocated_string::char_type const* str, int len) : base() {
   // Forward to basic_string::__ct
   call_class_func<void, char_type const*, int, void*>(0x8033e194, this, str, len, nullptr);
}

allocated_string::allocated_string(base const& str) : base() {
   if (str._cow_data == nullptr) {
      call_class_func<void, char_type const*, int, void*>(0x8033e194, this, str.data(),
                                                          static_cast<int>(str.size()), nullptr);
   } else {
      _data = str._data;
      _cow_data = str._cow_data;
      _size = str._size;
      if (_cow_data != nullptr) {
         _cow_data->ref_count++;
      }
   }
}

void allocated_string::append(allocated_string::char_type const* str, int len) {
   // forward to basic_string::append
   call_class_func<void, char_type const*, int>(0x8033dee4, this, str, len);
}

void allocated_string::append(allocated_string const& str) {
   // forward to basic_string::append
   call_class_func<void, allocated_string const&>(0x8033e038, this, str);
}

void allocated_string::append(allocated_string::base const& str) {
   if (str._cow_data == nullptr) {
      append(str.data(), str.size());
   } else {
      append(static_cast<allocated_string const&>(str));
   }
}

allocated_string& allocated_string::operator=(allocated_string::char_type const* rhs) {
   internal_dereference();
   call_class_func<void, char_type const*, int, void*>(0x8033e194, this, rhs, -1, nullptr);
   return *this;
}

allocated_string& allocated_string::operator=(allocated_string const& rhs) {
   internal_dereference();
   _data = rhs._data;
   _size = rhs._size;

   _cow_data = const_cast<COWData*>(rhs._cow_data);
   if (_cow_data != nullptr) {
      _cow_data->ref_count++;
   }
   return *this;
}

allocated_string& allocated_string::operator=(allocated_string::base const& rhs) {
   if (rhs.data() == nullptr) {
      allocated_string::operator=(rhs.data());
   } else {
      allocated_string::operator=(static_cast<allocated_string const&>(rhs));
   }
   return *this;
}

allocated_string allocated_string::substr(int beg, int end) const {
   return call_class_func<allocated_string, int, int>(0x8021d0c8, this, beg, end);
}

allocated_string operator+(string_base const& lhs, string_base const& rhs) {
   return call_func<allocated_string, string_base const&, string_base const&>(0x80004c5c, lhs, rhs);
}

allocated_string operator+(string_base const& lhs, string_base::char_type const* rhs) {
   return call_func<allocated_string, string_base const&, string_base::char_type const*>(0x8020c0f4,
                                                                                         lhs, rhs);
}
}  // namespace rstl
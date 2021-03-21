#pragma once

#include <type_traits>
#include <utility>

#include "freestanding.hh"
#include "mp1/rstl/utility.hh"

namespace rstl {

template <typename T>
class _vector_base {
public:
   class const_iterator {
   protected:
      T const* _it;

   public:
      explicit const_iterator(T const* it) : _it(it) {}
      T const& operator*() const { return *_it; }
      T const* operator->() const { return _it; }
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
      T const& operator[](ptrdiff_t i) const { return _it[i]; }
   };

   class iterator : public const_iterator {
   public:
      explicit iterator(T* it) : const_iterator(it) {}
      T& operator*() const { return *const_cast<T*>(const_iterator::_it); }
      T* operator->() const { return const_cast<T*>(const_iterator::_it); }
      iterator& operator++() {
         ++const_iterator::_it;
         return *this;
      }
      iterator& operator--() {
         --const_iterator::_it;
         return *this;
      }
      iterator operator++(int) {
         auto ret = *this;
         ++const_iterator::_it;
         return ret;
      }
      iterator operator--(int) {
         auto ret = *this;
         --const_iterator::_it;
         return ret;
      }
      iterator operator+(ptrdiff_t i) const {
         return iterator(const_cast<T*>(const_iterator::_it) + i);
      }
      iterator operator-(ptrdiff_t i) const {
         return iterator(const_cast<T*>(const_iterator::_it) - i);
      }
      iterator& operator+=(ptrdiff_t i) {
         const_iterator::_it += i;
         return *this;
      }
      iterator& operator-=(ptrdiff_t i) {
         const_iterator::_it -= i;
         return *this;
      }
      ptrdiff_t operator-(iterator const& rhs) const {
         return const_iterator::_it - rhs.const_iterator::_it;
      }
      bool operator>(iterator const& rhs) const {
         return const_iterator::_it > rhs.const_iterator::_it;
      }
      bool operator<(iterator const& rhs) const {
         return const_iterator::_it < rhs.const_iterator::_it;
      }
      bool operator>=(iterator const& rhs) const {
         return const_iterator::_it >= rhs.const_iterator::_it;
      }
      bool operator<=(iterator const& rhs) const {
         return const_iterator::_it <= rhs.const_iterator::_it;
      }
      T& operator[](ptrdiff_t i) const { return const_cast<T*>(const_iterator::_it)[i]; }
   };

   constexpr iterator const_cast_iterator(const_iterator it) {
      return iterator(const_cast<T*>(it._it));
   }
};

// Largely copied from URDE, cut out some STL references
template <typename T, size_t N>
class reserved_vector : public _vector_base<T> {
private:
   using base = _vector_base<T>;

public:
   using iterator = typename base::iterator;
   using const_iterator = typename base::const_iterator;

private:
   // Utilities
   union alignas(T) storage_t {
      struct {
      } _dummy;
      T _value;
      storage_t() : _dummy() {}
      ~storage_t() {}
   };

   T& _get(ptrdiff_t idx) { return _storage[idx]._value; }
   T const& _get(ptrdiff_t idx) const { return _storage[idx]._value; }

private:
   // Data Members
   size_t _size;
   storage_t _storage[N];

   // Shortened with constexpr if
   template <typename Tp>
   static void destroy(Tp& v) {
      if constexpr (std::is_destructible_v<Tp> && !std::is_trivially_destructible_v<Tp>) {
         v.Tp::~Tp();
      }
   }

public:
   reserved_vector() : _size(0) {}

   void push_back(T const& v) {
      utility::placement_new(_get(_size), v);
      ++_size;
   }

   void push_back(T&& v) {
      utility::placement_new(_get(_size), std::forward<T>(v));
      ++_size;
   }

   template <typename... TArgs>
   T& emplace_back(TArgs... args) {
      T& ret = _get(_size);
      utility::placement_new(_get(_size), std::forward<TArgs>(args)...);

      ++_size;
      return ret;
   }

   void pop_back() {
      --_size;
      destroy(_get(_size));
   }

   iterator insert(const_iterator pos, T const& val) {
      iterator target_pos = base::const_cast_iterator(pos);
      if (target_pos == end()) {
         push_back(val);
      } else {
         utility::placement_new(_get(_size), std::forward<T>(_get(_size - 1)));
         for (auto it = end() - 1; it != target_pos; --it) {
            *it = std::forward<T>(*(it - 1));
         }
         *target_pos = val;
         ++_size;
      }
      return target_pos;
   }

   iterator insert(const_iterator pos, T&& val) {
      iterator target_pos = base::const_cast_iterator(pos);
      if (target_pos == end()) {
         push_back(val);
      } else {
         utility::placement_new(_get(_size), std::forward<T>(_get(_size - 1)));
         for (auto it = end() - 1; it != target_pos; --it) {
            *it = std::forward<T>(*(it - 1));
         }
         *target_pos = std::forward<T>(val);
         ++_size;
      }
      return target_pos;
   }

   void resize(size_t size) {
      if (size > _size) {
         for (size_t i = _size; i < size; ++i) {
            utility::placement_new(_get(i), T());
         }
         _size = size;
      } else if (size < _size) {
         if constexpr (std::is_destructible_v<T> && !std::is_trivially_destructible_v<T>) {
            for (size_t i = size; i < _size; ++i) {
               destroy(_get(i));
            }
         }
         _size = size;
      }
   }

   iterator erase(const_iterator pos) {
      for (auto it = base::const_cast_iterator(pos) + 1; it != end(); ++it) {
         *(it - 1) = std::forward<T>(*it);
      }
      --_size;
      destroy(_get(_size));
      return base::const_cast_iterator(pos);
   }

   void pop_front() {
      if (_size != 0) {
         erase(begin());
      }
   }

   void clear() { resize(0); }

   size_t size() const { return _size; }
   bool empty() const { return _size == 0; }
   constexpr size_t capacity() const { return N; }
   T const* data() const { return utility::addressof(_get(0)); }
   T* data() { return utility::addressof(_get(0)); }

   T& back() { return _get(_size - 1); }
   T& front() { return _get(0); }
   T const& back() const { return _get(_size - 1); }
   T const& front() const { return _get(0); }

   iterator begin() { return iterator(utility::addressof(_get(0))); }
   iterator end() { return iterator(utility::addressof(_get(_size))); }
   const_iterator begin() const { return const_iterator(utility::addressof(_get(0))); }
   const_iterator end() const { return const_iterator(utility::addressof(_get(_size))); }

   T& operator[](size_t idx) { return _get(idx); }
   T const& operator[](size_t idx) const { return _get(idx); }

   ~reserved_vector() {
      if constexpr (std::is_destructible_v<T> && !std::is_trivially_destructible_v<T>) {
         for (size_t i = 0; i < _size; ++i) {
            destroy(_get(i));
         }
      }
   }
};

// Non-owning view of a vector, mimicking rstl::vector
// Built to be copied from by game-allocator
// DO NOT MOVE DIRECTLY INTO GAME OBJECTS!!
template <typename T>
class vector_noalloc : public _vector_base<T> {
public:
   using base = _vector_base<T>;
   using iterator = typename base::iterator;
   using const_iterator = typename base::const_iterator;

private:
   T& _get(ptrdiff_t idx) { return _data[idx]; }
   T const& _get(ptrdiff_t idx) const { return _data[idx]; }

private:
   void* _unk;
   size_t _size;
   size_t _capacity;
   T* _data;
   
   // Shortened with constexpr if
   template <typename Tp>
   static void destroy(Tp& v) {
      if constexpr (std::is_destructible_v<Tp> && !std::is_trivially_destructible_v<Tp>) {
         v.Tp::~Tp();
      }
   }

public:
   vector_noalloc() = delete;
   vector_noalloc(size_t size, size_t cap, T* data)
       : _unk(nullptr), _size(size), _capacity(cap), _data(data) {}

   iterator begin() { return iterator(utility::addressof(_get(0))); }
   const_iterator begin() const { return const_iterator(utility::addressof(_get(0))); }
   iterator end() { return iterator(utility::addressof(_get(_size))); }
   const_iterator end() const { return const_iterator(utility::addressof(_get(_size))); }

   T& front() { return _get(0); }
   T const& front() const { return _get(0); }
   T& back() { return _get(_size - 1); }
   T const& back() const { return _get(_size - 1); }

   T& operator[](size_t idx) { return _get(idx); }
   T const& operator[](size_t idx) const { return _get(idx); }

   size_t size() const { return _size; }
   bool empty() const { return _size == 0; }
   constexpr size_t capacity() const { return _capacity; }
   T const* data() const { return utility::addressof(_get(0)); }
   T* data() { return utility::addressof(_get(0)); }

   void clear() {
      if constexpr (std::is_destructible_v<T> && !std::is_trivially_destructible_v<T>) {
         for (size_t i = 0; i < _size; ++i) {
            destroy(_get(i));
         }
      }
      _size = 0;
   }
};

template <typename T>
using vector = vector_noalloc<T>;

// template <typename T>
// struct list {
//    struct node {
//       node* previous;
//       node* next;
//       uint32_t listnode_unk1;
//       T* data;
//       // There may be more, not like it matters
//    };

//    class list_iterator {
//       node* cur;

//    public:
//       list_iterator(node* start) : cur(start) {}
//       list_iterator& operator++() {
//          cur = cur->next;
//          return *this;
//       }

//       T* operator->() { return cur->data; };
//       T& operator*() { return *cur->data; }
//    };

//    class const_list_iterator {
//       node const* cur;

//    public:
//       const_list_iterator(node const* start) : cur(start) {}
//       const_list_iterator& operator++() {
//          cur = cur->next;
//          return *this;
//       }

//       T const* operator->() const { return cur->data; }
//       T const& operator*() const { return *cur->data; }
//    };

//    uint32_t list_unk1;
//    node* head;
//    node* after_end;
//    node* tail;
//    node* head_copy;
//    uint32_t length;

//    list_iterator begin() { return list_iterator(head); }
//    list_iterator end() { return list_iterator(end); }
//    const_list_iterator begin() const { return const_list_iterator(head); }
//    const_list_iterator end() const { return const_list_iterator(end); }
// };

}  // namespace rstl
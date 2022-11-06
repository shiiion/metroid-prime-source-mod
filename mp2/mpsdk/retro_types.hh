#pragma once

#include "freestanding.hh"

// Cloned from URDE

class CAssetId {
   u32 id = UINT32_MAX;

public:
   constexpr CAssetId() = default;
   constexpr CAssetId(u32 v) { assign(v); }
   constexpr bool is_valid() const { return id != UINT32_MAX; }
   constexpr u32 value() const { return id; }
   constexpr void assign(u32 v) { id = (v == 0 ? UINT32_MAX : v); }
   constexpr void reset() { id = UINT32_MAX; }
   constexpr bool operator==(CAssetId other) const { return id == other.id; }
   constexpr bool operator!=(CAssetId other) const { return !operator==(other); }
   constexpr bool operator<(CAssetId other) const { return id < other.id; }
   // TODO: PutTo/ctor
};

struct SObjectTag {
   uint32_t fourcc_type;
   CAssetId id;

   constexpr explicit operator bool() const { return id.is_valid(); }
   constexpr bool operator==(const SObjectTag& other) const { return id == other.id; }
   constexpr bool operator!=(const SObjectTag& other) const { return !operator==(other); }
   constexpr bool operator<(const SObjectTag& other) const { return id < other.id; }
   SObjectTag() = default;
   constexpr SObjectTag(uint32_t fcc, CAssetId id) : fourcc_type(fcc), id(id) {}
};

struct TEditorId {
   inline static constexpr u32 kLayerNumMask = 0x3f << 26;
   inline static constexpr u32 kAreaNumMask = 0x3ff << 16;
   inline static constexpr u32 kIdMask = 0xffff;
   u32 _id = UINT32_MAX;

   constexpr TEditorId() = default;
   constexpr TEditorId(u32 _id) : _id(_id) {}
   constexpr u8 layer_num() const { return static_cast<u8>((_id & kLayerNumMask) >> 26); }
   constexpr u16 area_num() const { return static_cast<u16>((_id & kAreaNumMask) >> 16); }
   constexpr u16 id() const { return static_cast<u16>(_id & kIdMask); }
   constexpr bool operator<(TEditorId other) const {
      return (_id & (kIdMask | kAreaNumMask)) == (other._id & (kIdMask | kAreaNumMask));
   }
   constexpr bool operator==(TEditorId other) const {
      return (_id & (kIdMask | kAreaNumMask)) == (other._id & (kIdMask | kAreaNumMask));
   }
   constexpr bool operator!=(TEditorId other) const { return !operator==(other); }
};
constexpr TEditorId kInvalidEditorId = TEditorId();

struct TUniqueId {
   inline static constexpr u16 kVersionMask = 0x3f << 10;
   inline static constexpr u16 kIdMask = 0x3ff;
   u16 _id = UINT16_MAX;

   constexpr TUniqueId() = default;
   constexpr TUniqueId(u16 value, u16 version) : _id(value | (version << 10)) {}
   constexpr u16 version() const { return static_cast<u16>((_id & kVersionMask) >> 10); }
   constexpr u16 value() const { return static_cast<u16>(_id & kIdMask); }
   constexpr bool operator<(TEditorId other) const { return _id < other._id; }
   constexpr bool operator==(TEditorId other) const { return _id == other._id; }
   constexpr bool operator!=(TEditorId other) const { return !operator==(other); }
};
constexpr TUniqueId kInvalidUniqueId = TUniqueId();

using TAreaId = s32;
constexpr TAreaId kInvalidAreaId = -1;

union CColor {
   u32 rgba;
   struct {
      u8 r, g, b, a;
   };

   constexpr CColor(u32 rgba) : rgba(rgba) {}
   constexpr CColor(u8 r, u8 g, u8 b, u8 a) : r(r), g(g), b(b), a(a) {}
};

#pragma once

#include "freestanding.hh"
#include "mp1/mpsdk/retro_types.hh"
#include "mp1/mpsdk/token.hh"
#include "mp1/rstl/optional.hh"
#include "mp1/rstl/string.hh"
#include "mp1/rstl/vector.hh"
#include "util/func_caller.hh"

enum class EJustification {
   Left = 0,
   Center,
   Right,
   Full,
   NLeft,
   NCenter,
   NRight,
   LeftMono,
   CenterMono,
   RightMono,
};

enum class EVerticalJustification {
   Top = 0,
   Center,
   Bottom,
   Full,
   NTop,
   NCenter,
   NBottom,
   TopMono,
   CenterMono,
   RightMono,
};

enum class ETextDirection {
   Horizontal,
   Vertical,
};

struct CGuiTextProperties {
   bool word_wrap;
   bool horizontal;
   EJustification justification;
   EVerticalJustification vertical_justification;
   rstl::vector<std::pair<CAssetId, CAssetId>> const* txtr_map;

   CGuiTextProperties(bool word_wrap, bool horizontal, EJustification justification,
                      EVerticalJustification vertical_justification,
                      rstl::vector<std::pair<CAssetId, CAssetId>> const* txtr_map)
       : word_wrap(word_wrap),
         horizontal(horizontal),
         justification(justification),
         vertical_justification(vertical_justification),
         txtr_map(txtr_map) {}
};

class CGuiTextSupport {
private:
   rstl::string string;
   float cur_time_mod_900;
   CGuiTextProperties props;
   CColor font_color;
   CColor outline_color;
   CColor geometry_color;
   bool image_baseline;
   s32 extent_x;
   s32 extent_y;
   float cur_time;
   rstl::vector<std::pair<float, int>> prim_start_times;
   bool type_enable;
   float ch_fade_time;
   float ch_rate;
   CAssetId font_id;
   rstl::optional<u8[0x258]> unused__render_buf;
   rstl::vector<CToken> assets;
   CToken font;
   u8 padding__1[0x8];
   int bounds_x_1, bounds_y_1;
   int bounds_x_2, bounds_y_2;
   u8 padding__2[0x18];
   int page_counter;
   bool multipage_flag;

public:
   static CGuiTextSupport* create_debug_print(float scale_factor);
   void prepare_for_render();
   void update(float dt) { call_class_func<void, float>(0x802c8178, this, dt); }
   void render() { call_class_func<void>(0x802c9544, this); }
   void set_text(rstl::string_base const& str) {
      call_class_func<void*, rstl::string_base const&, bool>(0x802c9b08, this, str, false);
   }
   void destroy() { call_class_func<void, int>(0x802c9c98, this, 0); }
};
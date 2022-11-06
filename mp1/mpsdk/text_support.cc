#include "mp1/mpsdk/text_support.hh"

#include "mp1/mpsdk/alloc.hh"
#include "util/r_math.hh"

CGuiTextSupport* CGuiTextSupport::create_debug_print(float scale_factor) {
   CGuiTextSupport* inst = alloc_inst<CGuiTextSupport>();
   CGuiTextProperties properties(true, true, EJustification::Left, EVerticalJustification::Top,
                                 nullptr);
   constexpr CAssetId font(0xb5bc844e);
   constexpr CColor font_color(0xffffffff);
   constexpr CColor font_outline_color(0xffffffff);
   scale_factor = 1.f / scale_factor;
   s32 x_ext = static_cast<s32>(640.f * scale_factor);
   s32 y_ext = static_cast<s32>(448.f * scale_factor);
   void* const global_simple_pool = reinterpret_cast<void*>(0x80457864);

   call_class_func<void, u32, CGuiTextProperties const&, CColor const&, CColor const&,
                   CColor const&, s32, s32, void*>(0x802c9e3c, inst, font.value(), properties,
                                                   font_color, font_outline_color, font_color,
                                                   x_ext, y_ext, global_simple_pool);
   call_class_func<void, bool, float, float>(0x802c8118, inst, false, 0.f, 0.f);
   return inst;
}

void CGuiTextSupport::prepare_for_render() {
   // CCubeRenderer::SetViewportOrtho
   call_func<vec4, void*, bool, float, float>(0x802bc8c4, nullptr, false, -4096.f, 4096.f);
   // CGraphics::SetModelMatrix
   const float scale_x = 640.f / static_cast<float>(extent_x);
   const float scale_y = 448.f / static_cast<float>(extent_y);
   mat34 mv_matrix = mat34::scale(scale_x, 1.f, scale_y) * mat34::translate(0.f, 0.f, 448.f / scale_y);
   call_func<void, mat34 const&>(0x8030c5e0, mv_matrix);
   // CGraphics::SetCullMode
   call_func<void, int>(0x8030ba70, 0);
   // CCubeRenderer::SetDepthReadWrite
   call_func<void, void*, bool, bool>(0x802bc828, nullptr, false, false);
   // CCubeRenderer::SetBlendMode_AdditiveAlpha
   call_func<void, void*>(0x802bc7f8, nullptr);
}

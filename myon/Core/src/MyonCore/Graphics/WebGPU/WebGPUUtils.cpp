// clang-format off
#include "MyonCore/Graphics/WebGPU/WebGPUUtils.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {

std::string_view toStdStringView(WGPUStringView p_wgpuStringView) {
  std::string_view stringview(p_wgpuStringView.data, p_wgpuStringView.length);
  return stringview;
}

WGPUStringView toWGPUStringView(std::string p_stdString) {
  WGPUStringView wgpustringview = {p_stdString.data(), p_stdString.size()};
  return wgpustringview;
}

} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

// clang-format off
#include <cstring>

#include "MyonCore/Graphics/WebGPU/WebGPUUtils.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {

std::string_view toStdStringView(WGPUStringView p_wgpuStringView) {
  return std::string_view(p_wgpuStringView.data, p_wgpuStringView.length);
}

WGPUStringView toWGPUStringView(const std::string &p_stdString) {
  WGPUStringView wgpustringview = {p_stdString.data(), p_stdString.size()};
  return wgpustringview;
}

WGPUStringView toWGPUStringView(const char *p_stringliteral) {
  return {p_stringliteral, strlen(p_stringliteral)};
}

} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

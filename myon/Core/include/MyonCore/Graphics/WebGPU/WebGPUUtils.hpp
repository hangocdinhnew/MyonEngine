#pragma once

// clang-format off
#include <string>
#include <webgpu/webgpu.h>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {

// Strings
std::string_view toStdStringView(WGPUStringView p_wgpuStringView);
WGPUStringView toWGPUStringView(std::string p_stdString);

} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

#pragma once

// clang-format off
#include <string>
#include <functional>

#include <webgpu/webgpu.h>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
// Strings
std::string_view toStdStringView(WGPUStringView p_wgpuStringView);
WGPUStringView toWGPUStringView(const std::string &p_stdString);
WGPUStringView toWGPUStringView(const char *p_stringliteral);

// Sleep
void sleepForMSec(unsigned int msec);

// Fetch Buffer Data Sync
void fetchBufferDataSync(WGPUInstance instance, WGPUBuffer bufferB,
                         WGPUBufferDescriptor bufferBDesc,
                         std::function<void(const void *)> processBufferData);
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

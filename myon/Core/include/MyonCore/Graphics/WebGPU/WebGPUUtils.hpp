#pragma once

// clang-format off
#include <string>
#include <functional>

#include <webgpu/webgpu.hpp>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
// Strings
std::string_view toStdStringView(wgpu::StringView p_wgpuStringView);
wgpu::StringView toWGPUStringView(const std::string &p_stdString);
wgpu::StringView toWGPUStringView(const char *p_stringliteral);

// Sleep
void sleepForMSec(unsigned int msec);

// Fetch Buffer Data Sync
void fetchBufferDataSync(wgpu::Instance instance, wgpu::Buffer bufferB,
                         wgpu::BufferDescriptor bufferBDesc,
                         std::function<void(const void *)> processBufferData);
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

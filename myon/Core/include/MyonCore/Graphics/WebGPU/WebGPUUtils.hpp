#pragma once

// clang-format off
#include <string>
#include <functional>

#include <webgpu/webgpu.h>
// clang-format on

#define ELEMENT_COUNT 64

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
                         std::function<void(const void *)> processBufferData);

// Loading shaders
std::string getExecutablePath();
WGPUStringView loadShader(const std::string& folderName, const std::string& filePath);
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

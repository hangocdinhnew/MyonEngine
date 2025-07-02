// clang-format off
#include <cstring>
#include <thread>
#include <chrono>

#include "MyonCore/Graphics/WebGPU/WebGPUUtils.hpp"
#include "MyonCore/Core/Log.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#elif defined(__linux__)
#include <unistd.h>
#elif defined(__FreeBSD__)
#include <unistd.h>
#include <sys/sysctl.h>
#elif defined(_WIN32)
// Windows doesn't need exec path logic per requirements
#else
#error Unsupported platform
#endif
//
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
std::string_view toStdStringView(WGPUStringView p_wgpuStringView) {
  return std::string_view(p_wgpuStringView.data, p_wgpuStringView.length);
}

WGPUStringView toWGPUStringView(const std::string &p_stdString) {
  return {p_stdString.data(), p_stdString.size()};
}

WGPUStringView toWGPUStringView(const char *p_stringliteral) {
  return {p_stringliteral, strlen(p_stringliteral)};
}

void sleepForMSec(unsigned int msec) {
  std::this_thread::sleep_for(std::chrono::milliseconds(msec));
}

void fetchBufferDataSync(WGPUInstance instance, WGPUBuffer bufferB,
                         std::function<void(const void *)> processBufferData) {
  struct OnBufferBMappedContext {
    bool operationEnded = false;
    bool mappingIsSuccessful = false;
  };

  auto onBufferBMapped = [](WGPUMapAsyncStatus status,
                            struct WGPUStringView message, void *userdata1,
                            void *) {
    OnBufferBMappedContext &context =
        *reinterpret_cast<OnBufferBMappedContext *>(userdata1);
    context.operationEnded = true;
    if (status == WGPUMapAsyncStatus_Success) {
      context.mappingIsSuccessful = true;
    } else {
      MYON_CORE_INFO("WebGPU - Could not map buffer B! tatus: {}, message: {}",
                     static_cast<int>(status), toStdStringView(message));
    }
  };

  OnBufferBMappedContext context;

  WGPUBufferMapCallbackInfo callbackInfo = {};
  callbackInfo.mode = WGPUCallbackMode_AllowProcessEvents;
  callbackInfo.callback = onBufferBMapped;
  callbackInfo.userdata1 = &context;

  wgpuBufferMapAsync(bufferB, WGPUMapMode_Read, 0,
                     ELEMENT_COUNT * sizeof(float), callbackInfo);

  wgpuInstanceProcessEvents(instance);
  while (!context.operationEnded) {
    sleepForMSec(200);

    wgpuInstanceProcessEvents(instance);
  }

  if (context.mappingIsSuccessful) {
    const void *bufferData = wgpuBufferGetConstMappedRange(
        bufferB, 0, ELEMENT_COUNT * sizeof(float));
    processBufferData(bufferData);
  }
}

std::string getExecutablePath() {
#if defined(__APPLE__)
  char buffer[1024];
  uint32_t size = sizeof(buffer);
  if (_NSGetExecutablePath(buffer, &size) != 0) {
    throw std::runtime_error("Failed to get executable path: buffer too small");
  }
  return std::string(buffer);
#elif defined(__linux__)
  char buffer[1024];
  ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
  if (len == -1) {
    throw std::runtime_error("Failed to read /proc/self/exe");
  }
  buffer[len] = '\0';
  return std::string(buffer);
#elif defined(__FreeBSD__)
  char buffer[1024];
  int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1};
  size_t size = sizeof(buffer);
  if (sysctl(mib, 4, buffer, &size, NULL, 0) == -1) {
    throw std::runtime_error("Failed to get executable path via sysctl");
  }
  return std::string(buffer);
#else
  throw std::runtime_error("Unsupported Unix-like platform");
#endif
}

WGPUStringView loadShader(const std::string &folderName,
                          const std::string &filePath) {
  std::string fullPath;

#if defined(_WIN32)
  fullPath = "assets/shaders/" + filePath;
#else
  std::string execPath = getExecutablePath();
  std::string::size_type lastSlash = execPath.find_last_of('/');
  if (lastSlash == std::string::npos) {
    throw std::runtime_error("Executable path is malformed");
  }

  std::string basePath = execPath.substr(0, lastSlash);
  fullPath =
      basePath + "/../share/" + folderName + "/assets/shaders/" + filePath;
#endif

  std::ifstream file(fullPath, std::ios::binary);
  if (!file) {
    MYON_DO_CORE_ASSERT("Failed to open shader file: {}", fullPath);
  }

  std::ostringstream ss;
  ss << file.rdbuf();
  std::string *shaderContent = new std::string(ss.str());

  return toWGPUStringView(*shaderContent);
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

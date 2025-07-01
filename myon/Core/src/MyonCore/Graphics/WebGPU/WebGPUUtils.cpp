// clang-format off
#include <cstring>
#include <thread>
#include <chrono>

#include "MyonCore/Graphics/WebGPU/WebGPUUtils.hpp"
#include "MyonCore/Core/Log.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
std::string_view toStdStringView(wgpu::StringView p_wgpuStringView) {
  return std::string_view(p_wgpuStringView.data, p_wgpuStringView.length);
}

wgpu::StringView toWGPUStringView(const std::string &p_stdString) {
  return wgpu::StringView(p_stdString);
}

wgpu::StringView toWGPUStringView(const char *p_stringliteral) {
  return wgpu::StringView(std::string_view(p_stringliteral));
}

void sleepForMSec(unsigned int msec) {
  std::this_thread::sleep_for(std::chrono::milliseconds(msec));
}

void fetchBufferDataSync(wgpu::Instance instance, wgpu::Buffer bufferB,
                         wgpu::BufferDescriptor bufferBDesc,
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

  wgpu::BufferMapCallbackInfo callbackInfo = {};
  callbackInfo.mode = WGPUCallbackMode_AllowProcessEvents;
  callbackInfo.callback = onBufferBMapped;
  callbackInfo.userdata1 = &context;

  bufferB.mapAsync(WGPUMapMode_Read, 0, bufferBDesc.size, callbackInfo);

  instance.processEvents();
  while (!context.operationEnded) {
    sleepForMSec(200);

    instance.processEvents();
  }

  if (context.mappingIsSuccessful) {
    const void *bufferData = bufferB.getConstMappedRange(0, bufferBDesc.size);
    processBufferData(bufferData);
  }
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

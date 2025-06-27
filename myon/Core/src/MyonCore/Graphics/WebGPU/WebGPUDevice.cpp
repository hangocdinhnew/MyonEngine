// clang-format off
#include "MyonCore/Core/Log.hpp"
#include <string_view>
#include <webgpu.h>
#include "MyonCore/Graphics/WebGPU/WebGPUDevice.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
static WGPUDevice requestDeviceSync(WGPUAdapter adapter,
                                    WGPUDeviceDescriptor const *descriptor) {
  struct UserData {
    WGPUDevice device = nullptr;
    bool requestEnded = false;
  };
  UserData userData;

  auto onDeviceRequestEnded = [](WGPURequestDeviceStatus status,
                                 WGPUDevice device,
                                 WGPUStringView strview_message,
                                 void *pUserData1, void *pUserData2) {
    UserData &userData = *reinterpret_cast<UserData *>(pUserData1);
    if (status == WGPURequestDeviceStatus_Success) {
      userData.device = device;
    } else {
      std::string_view message(strview_message.data, strview_message.length);
      MYON_DO_CORE_ASSERT("Could not get WebGPU device: {}", message);
    }
    userData.requestEnded = true;
  };

  WGPURequestDeviceCallbackInfo deviceCallbackInfo = {};
  deviceCallbackInfo.nextInChain = nullptr;
  deviceCallbackInfo.callback = onDeviceRequestEnded;
  deviceCallbackInfo.userdata1 = &userData;
  deviceCallbackInfo.userdata2 = nullptr;

  wgpuAdapterRequestDevice(adapter, descriptor, deviceCallbackInfo);

#ifdef __EMSCRIPTEN__
  while (!userData.requestEnded) {
    emscripten_sleep(100);
  }
#endif // __EMSCRIPTEN__

  MYON_CORE_ASSERT(!userData.requestEnded,
                   "WebGPU - WebGPU device request never completed!");

  return userData.device;
}

WebGPUDevice::WebGPUDevice(WebGPUDeviceConfig &p_DeviceConfig)
    : m_Adapter(p_DeviceConfig.p_Adapter), m_Name(p_DeviceConfig.p_Name) {
  MYON_CORE_ASSERT(!m_Adapter.has_value(), "Device - Failed to access m_Adapter!");
  MYON_CORE_ASSERT(!m_Name.has_value(), "Device - Failed to access m_Name!");

  WGPUDeviceDescriptor deviceDesc = {};
  deviceDesc.nextInChain = nullptr;
  std::string label = m_Name.value();
  WGPUStringView strview_label = {label.c_str(), label.length()};

  std::string defaultQueuelabel = "The default queue";
  WGPUStringView strview_defaultQueuelabel = {defaultQueuelabel.c_str(),
                                              defaultQueuelabel.length()};

  WGPUDeviceLostCallbackInfo deviceLostCallbackInfo = {};
  deviceLostCallbackInfo.callback = [](WGPUDevice const *,
                                       WGPUDeviceLostReason reason,
                                       WGPUStringView message, void *, void *) {
    std::string convertedreason;

    switch (reason) {
    case WGPUDeviceLostReason_Destroyed:
      convertedreason = "WebGPU Device destroyed";
      break;
    case WGPUDeviceLostReason_InstanceDropped:
      convertedreason = "WebGPU Instance dropped";
      break;
    case WGPUDeviceLostReason_FailedCreation:
      convertedreason = "WebGPU Device Creation Failed";
      break;
    default:
      convertedreason = &""[static_cast<int>(reason)];
      break;
    }

    MYON_CORE_ERROR("WebGPU - WebGPU Device lost! Reason: {}.", convertedreason);
    std::string_view conv_message = {message.data, message.length};

    MYON_DO_CORE_ASSERT("WebGPU\t- Message: {}", conv_message);
  };

  deviceDesc.label = strview_label;
  deviceDesc.requiredFeatureCount = 0;
  deviceDesc.requiredLimits = nullptr;
  deviceDesc.defaultQueue.nextInChain = nullptr;
  deviceDesc.defaultQueue.label = strview_defaultQueuelabel;
  deviceDesc.deviceLostCallbackInfo = deviceLostCallbackInfo;

  m_Device = requestDeviceSync(m_Adapter.value(), &deviceDesc);

  MYON_CORE_ASSERT(!m_Device, "WebGPU - Failed to create WebGPU Device!");

  MYON_CORE_INFO("WebGPU - WebGPU Device created!");
}

WebGPUDevice::~WebGPUDevice() {
  MYON_CORE_INFO("WebGPU - Releasing WebGPU Device...");

  wgpuDeviceRelease(m_Device);
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

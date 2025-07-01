// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUUtils.hpp"
#include <string_view>
#include <webgpu/wgpu.h>
#include <webgpu/webgpu.h>
#include "MyonCore/Graphics/WebGPU/WebGPUDevice.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
static wgpu::Device requestDeviceSync(wgpu::Instance instance,
                                      wgpu::Adapter adapter,
                                      wgpu::DeviceDescriptor const descriptor) {
  struct UserData {
    wgpu::Device device = nullptr;
    bool requestEnded = false;
  };
  UserData userData;

  auto onDeviceRequestEnded = [](WGPURequestDeviceStatus status,
                                 WGPUDevice device,
                                 WGPUStringView message,
                                 void *pUserData1, void *pUserData2) {
    UserData &userData = *reinterpret_cast<UserData *>(pUserData1);
    if (status == WGPURequestDeviceStatus_Success) {
      userData.device = device;
    } else {
      MYON_DO_CORE_ASSERT("Could not get WebGPU device: {}", toStdStringView(message));
    }
    userData.requestEnded = true;
  };

  wgpu::RequestDeviceCallbackInfo deviceCallbackInfo = {};
  deviceCallbackInfo.nextInChain = nullptr;
  deviceCallbackInfo.mode = wgpu::CallbackMode::AllowProcessEvents;
  deviceCallbackInfo.callback = onDeviceRequestEnded;
  deviceCallbackInfo.userdata1 = &userData;
  deviceCallbackInfo.userdata2 = nullptr;

  adapter.requestDevice(descriptor, deviceCallbackInfo);

  instance.processEvents();

  while (!userData.requestEnded) {
    sleepForMSec(200);

    instance.processEvents();
  }

  return userData.device;
}

WebGPUDevice::WebGPUDevice(WebGPUDeviceConfig &p_DeviceConfig)
    : m_Instance(p_DeviceConfig.p_Instance),
      m_Adapter(p_DeviceConfig.p_Adapter), m_Name(p_DeviceConfig.p_Name) {
  MYON_CORE_ASSERT(!m_Instance.has_value(),
                   "Device - Failed to access m_Instance!");
  MYON_CORE_ASSERT(!m_Adapter.has_value(),
                   "Device - Failed to access m_Adapter!");
  MYON_CORE_ASSERT(!m_Name.has_value(), "Device - Failed to access m_Name!");

  wgpu::DeviceDescriptor deviceDesc = {};
  deviceDesc.nextInChain = nullptr;

  wgpu::DeviceLostCallbackInfo deviceLostCallbackInfo = {};

  auto lostCallbackInfo = [](WGPUDevice const *, WGPUDeviceLostReason reason,
                             WGPUStringView message, void *, void *) {
    std::string convertedreason = "";

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
      convertedreason = static_cast<int>(reason);
      break;
    }

    MYON_CORE_ERROR("WebGPU - WebGPU Device lost! Reason: {}.",
                    convertedreason);
    MYON_DO_CORE_ASSERT("WebGPU\t- Message: {}", toStdStringView(message));
  };

  deviceLostCallbackInfo.callback = lostCallbackInfo;

  auto uncapturedErrorCallbackInfo =
      [](WGPUDevice const *device, WGPUErrorType type,
         struct WGPUStringView message, void *, void *) {
        std::string convtype = "";

        switch (type) {
        case WGPUErrorType_NoError:
          convtype = "NoError";
          break;
        case WGPUErrorType_Validation:
          convtype = "Validation";
          break;
        case WGPUErrorType_OutOfMemory:
          convtype = "OutOfMemory";
          break;
        case WGPUErrorType_Internal:
          convtype = "Internal";
          break;
        case WGPUErrorType_Unknown:
          convtype = "Unknown";
          break;
        default:
          convtype = static_cast<int>(type);
          break;
        }

        MYON_CORE_INFO("WebGPU - Uncaptured error (type: {}), device: {}",
                       convtype, (void *)device);
        MYON_DO_CORE_ASSERT("WebGPU - Message: {}", toStdStringView(message));
      };

  deviceDesc.uncapturedErrorCallbackInfo.callback = uncapturedErrorCallbackInfo;

  deviceDesc.label = toWGPUStringView(m_Name.value());
  deviceDesc.requiredFeatureCount = 0;
  deviceDesc.requiredLimits = nullptr;
  deviceDesc.defaultQueue.nextInChain = nullptr;
  deviceDesc.defaultQueue.label = toWGPUStringView("The default queue.");
  deviceDesc.deviceLostCallbackInfo = deviceLostCallbackInfo;

  m_Device =
      requestDeviceSync(m_Instance.value(), m_Adapter.value(), deviceDesc);

  MYON_CORE_ASSERT(!m_Device, "WebGPU - Failed to create WebGPU Device!");

  MYON_CORE_INFO("WebGPU - WebGPU Device created!");
}

WebGPUDevice::~WebGPUDevice() {
  MYON_CORE_INFO("WebGPU - Releasing WebGPU Device...");

  m_Device.release();
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

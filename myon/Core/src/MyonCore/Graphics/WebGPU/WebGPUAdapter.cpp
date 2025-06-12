// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUAdapter.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
static WGPUAdapter
requestAdapterSync(WGPUInstance instance,
                   WGPURequestAdapterOptions const *options) {
  struct UserData {
    WGPUAdapter adapter = nullptr;
    bool requestEnded = false;
  };
  UserData userData;

  auto onAdapterRequestEnded = [](WGPURequestAdapterStatus status,
                                  WGPUAdapter adapter, WGPUStringView message,
                                  void *pUserData1, void *pUserData2) {
    UserData &userData = *reinterpret_cast<UserData *>(pUserData1);
    if (status == WGPURequestAdapterStatus_Success) {
      userData.adapter = adapter;
    } else {
      std::string_view msgView(message.data, message.length);

      MYON_CORE_ERROR("WebGPU - Could not get WebGPU adapter: {}", msgView);
    }
    userData.requestEnded = true;
  };

  WGPURequestAdapterCallbackInfo callbackInfo = {};
  callbackInfo.nextInChain = nullptr;
  callbackInfo.callback = onAdapterRequestEnded;
  callbackInfo.userdata1 = &userData;

  wgpuInstanceRequestAdapter(instance, options, callbackInfo);

  MYON_CORE_ASSERT(!userData.requestEnded,
                   "WebGPU - WebGPU adapter request never completed!");

  return userData.adapter;
}

static void inspectAdapter(WGPUAdapter adapter) {
#ifdef MYON_DEBUG
  WGPULimits limits = {};
  limits.nextInChain = nullptr;

  bool success = wgpuAdapterGetLimits(adapter, &limits);
  if (success) {
    MYON_CORE_DEBUG("WebGPU - Adapter limits:");
    MYON_CORE_DEBUG("WebGPU -\tmaxTextureDimension1D: {}",
                    limits.maxTextureDimension1D);
    MYON_CORE_DEBUG("WebGPU -\tmaxTextureDimension2D: {}",
                    limits.maxTextureDimension2D);
    MYON_CORE_DEBUG("WebGPU -\tmaxTextureDimension3D: {}",
                    limits.maxTextureDimension3D);
    MYON_CORE_DEBUG("WebGPU -\tmaxTextureArrayLayers: {}",
                    limits.maxTextureArrayLayers);
  }

  WGPUSupportedFeatures supportedFeatures = {};
  wgpuAdapterGetFeatures(adapter, &supportedFeatures);

  MYON_CORE_DEBUG("WebGPU - Adapter features (hex):");
  for (uint32_t i = 0; i < supportedFeatures.featureCount; ++i) {
    MYON_CORE_DEBUG(" - 0x{:x}",
                    static_cast<uint32_t>(supportedFeatures.features[i]));
  }

  WGPUAdapterInfo info = {};
  info.nextInChain = nullptr;
  wgpuAdapterGetInfo(adapter, &info);

  MYON_CORE_DEBUG("WebGPU - Adapter properties:");
  MYON_CORE_DEBUG(" - vendorID: {}", info.vendorID);

  std::string_view vendorName(info.vendor.data, info.vendor.length);
  MYON_CORE_DEBUG(" - vendorName: {}", vendorName);

  std::string_view architecture(info.architecture.data,
                                info.architecture.length);
  MYON_CORE_DEBUG(" - architecture: {}", architecture);

  MYON_CORE_DEBUG(" - deviceID: {}", info.deviceID);

  std::string_view device(info.device.data, info.device.length);
  MYON_CORE_DEBUG(" - name: {}", device);

  std::string_view description(info.description.data, info.description.length);
  MYON_CORE_DEBUG(" - driverDescription: {}", description);

  MYON_CORE_DEBUG(" - adapterType: 0x{:x}", static_cast<int>(info.adapterType));
  MYON_CORE_DEBUG(" - backendType: 0x{:x}", static_cast<int>(info.backendType));
#endif
}

WebGPUAdapter::WebGPUAdapter(WebGPUAdapterConfig &p_AdapterConfig)
    : m_Instance(p_AdapterConfig.p_Instance) {
  WGPURequestAdapterOptions adapterOpts = {};
  adapterOpts.nextInChain = nullptr;
  m_Adapter = requestAdapterSync(m_Instance, &adapterOpts);

  MYON_CORE_ASSERT(!m_Adapter, "WebGPU - Failed to request Adapter sync!");

#ifdef MYON_DEBUG
  inspectAdapter(m_Adapter);
#endif

  MYON_CORE_INFO("WebGPU - WebGPU adapter synced!");
}

WebGPUAdapter::~WebGPUAdapter() {
  MYON_CORE_INFO("Releasing WebGPU Adapter!");

  wgpuAdapterRelease(m_Adapter);
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

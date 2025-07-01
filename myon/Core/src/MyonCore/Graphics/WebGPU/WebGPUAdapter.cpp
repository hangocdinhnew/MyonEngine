// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUUtils.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUAdapter.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
static wgpu::Adapter
requestAdapterSync(wgpu::Instance instance,
                   wgpu::RequestAdapterOptions const options) {
  struct UserData {
    wgpu::Adapter adapter = nullptr;
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
      std::string_view msgView = toStdStringView(message);

      MYON_CORE_ERROR("WebGPU - Could not get WebGPU adapter: {}", msgView);
    }
    userData.requestEnded = true;
  };

  wgpu::RequestAdapterCallbackInfo callbackInfo = {};
  callbackInfo.nextInChain = nullptr;
  callbackInfo.mode = wgpu::CallbackMode::AllowProcessEvents;
  callbackInfo.callback = onAdapterRequestEnded;
  callbackInfo.userdata1 = &userData;
  callbackInfo.userdata2 = nullptr;

  instance.requestAdapter(options, callbackInfo);

  instance.processEvents();

  while (!userData.requestEnded) {
    sleepForMSec(200);

    instance.processEvents();
  }

  return userData.adapter;
}

WebGPUAdapter::WebGPUAdapter(WebGPUAdapterConfig &p_AdapterConfig)
    : m_Instance(p_AdapterConfig.p_Instance),
      m_Surface(p_AdapterConfig.p_Surface) {
  MYON_CORE_ASSERT(!m_Instance.has_value(),
                   "Adapter - Failed to access m_Instance!");
  MYON_CORE_ASSERT(!m_Surface.has_value(),
                   "Adapter - Failed to access m_Surface!");

  wgpu::RequestAdapterOptions adapterOpts = {};
  adapterOpts.nextInChain = nullptr;
  adapterOpts.compatibleSurface = m_Surface.value();
  m_Adapter = requestAdapterSync(m_Instance.value(), adapterOpts);

  MYON_CORE_ASSERT(!m_Adapter, "WebGPU - Failed to request Adapter sync!");

  MYON_CORE_INFO("WebGPU - WebGPU adapter created!");
}

WebGPUAdapter::~WebGPUAdapter() {
  MYON_CORE_INFO("Releasing WebGPU Adapter!");

  m_Adapter.release();
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

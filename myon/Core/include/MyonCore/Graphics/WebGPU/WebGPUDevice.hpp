#pragma once

// clang-format off
#include <string>
#include <optional>
#include <webgpu/webgpu.h>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
struct WebGPUDeviceConfig {
  std::optional<std::string> p_Name;
  std::optional<WGPUAdapter> p_Adapter;
};

class WebGPUDevice {
public:
  WebGPUDevice(WebGPUDeviceConfig &p_DeviceConfig);
  ~WebGPUDevice();

  WGPUDevice &getDevice() { return m_Device; }

private:
  std::optional<std::string> &m_Name;
  std::optional<WGPUAdapter> &m_Adapter;

  WGPUDevice m_Device;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

#pragma once

// clang-format off
#include <string>
#include <optional>
#include <webgpu/webgpu.hpp>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
struct WebGPUDeviceConfig {
  std::optional<std::string> p_Name;
  std::optional<wgpu::Instance> p_Instance;
  std::optional<wgpu::Adapter> p_Adapter;
};

class WebGPUDevice {
public:
  WebGPUDevice(WebGPUDeviceConfig &p_DeviceConfig);
  ~WebGPUDevice();

  wgpu::Device &getDevice() { return m_Device; }

private:
  std::optional<std::string> &m_Name;
  std::optional<wgpu::Instance> &m_Instance;
  std::optional<wgpu::Adapter> &m_Adapter;

  wgpu::Device m_Device;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

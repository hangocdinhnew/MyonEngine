#pragma once

// clang-format off
#include <optional>

#include <webgpu/webgpu.h>

#include "MyonCore/Core/Log.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
struct WebGPUComputePipelineConfig {
  std::optional<WGPUDevice> p_Device;
  std::optional<WGPUBuffer> p_InputBuffer;
  std::optional<WGPUBuffer> p_OutputBuffer;
  std::optional<std::string> p_FolderName;
  std::optional<std::string> p_FilePath;
};

class WebGPUComputePipeline {
public:
  WebGPUComputePipeline(WebGPUComputePipelineConfig &p_ComputePipelineConfig);

  ~WebGPUComputePipeline();

  void Init(const std::string &folderName, const std::string &filePath);

  WGPUComputePipeline getComputePipeline() { return m_ComputePipeline; };
  WGPUBindGroup getBindGroup() { return m_BindGroup; };

private:
  std::optional<WGPUDevice> &m_Device;
  std::optional<WGPUBuffer> &m_InputBuffer;
  std::optional<WGPUBuffer> &m_OutputBuffer;
  std::optional<std::string> &m_FolderName;
  std::optional<std::string> &m_FilePath;

  WGPUComputePipeline m_ComputePipeline;
  WGPUBindGroup m_BindGroup;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

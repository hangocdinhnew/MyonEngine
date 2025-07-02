// clang-format off
#include "MyonCore/Graphics/WebGPU/WebGPUUtils.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUComputePipeline.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
WebGPUComputePipeline::WebGPUComputePipeline(
    WebGPUComputePipelineConfig &p_ComputePipelineConfig)
    : m_Device(p_ComputePipelineConfig.p_Device),
      m_InputBuffer(p_ComputePipelineConfig.p_InputBuffer),
      m_OutputBuffer(p_ComputePipelineConfig.p_OutputBuffer),
      m_FolderName(p_ComputePipelineConfig.p_FolderName),
      m_FilePath(p_ComputePipelineConfig.p_FilePath) {
  MYON_CORE_ASSERT(!m_Device.has_value(),
                   "Compute Pipeline - Failed to access m_Device!");
  MYON_CORE_ASSERT(!m_InputBuffer.has_value(),
                   "Compute Pipeline - Failed to access m_InputBuffer!");
  MYON_CORE_ASSERT(!m_OutputBuffer.has_value(),
                   "Compute Pipeline - Failed to access m_OutputBuffer!");
  MYON_CORE_ASSERT(!m_FolderName.has_value(),
                   "Compute Pipeline - Failed to access m_FolderName!");
  MYON_CORE_ASSERT(!m_FilePath.has_value(),
                   "Compute Pipeline - Failed to access m_FilePath!");

  WGPUShaderModuleDescriptor moduleDesc = {};
  moduleDesc.label = toWGPUStringView("Compute Shader Module");
  WGPUShaderSourceWGSL wgslSourceDesc = {};
  wgslSourceDesc.code = loadShader(m_FolderName.value(), m_FilePath.value());
  wgslSourceDesc.chain.sType = WGPUSType_ShaderSourceWGSL;
  wgslSourceDesc.chain.next = nullptr;
  moduleDesc.nextInChain = &wgslSourceDesc.chain;
  WGPUShaderModule shaderModule =
      wgpuDeviceCreateShaderModule(m_Device.value(), &moduleDesc);

  WGPUComputePipelineDescriptor pipelineDesc = {};
  pipelineDesc.label = toWGPUStringView("Compute Pipeline");
  pipelineDesc.compute.module = shaderModule;
  pipelineDesc.compute.entryPoint = toWGPUStringView("computeStuff");

  m_ComputePipeline =
      wgpuDeviceCreateComputePipeline(m_Device.value(), &pipelineDesc);

  wgpuShaderModuleRelease(shaderModule);
  std::vector<WGPUBindGroupEntry> bindGroupEntries(2);

  bindGroupEntries[0].binding = 0;
  bindGroupEntries[0].buffer = m_InputBuffer.value();
  bindGroupEntries[0].offset = 0;
  bindGroupEntries[0].size = ELEMENT_COUNT * sizeof(float);
  bindGroupEntries[0].nextInChain = nullptr;

  bindGroupEntries[1].binding = 1;
  bindGroupEntries[1].buffer = m_OutputBuffer.value();
  bindGroupEntries[1].offset = 0;
  bindGroupEntries[1].size = ELEMENT_COUNT * sizeof(float);
  bindGroupEntries[1].nextInChain = nullptr;

  WGPUBindGroupDescriptor bindGroupDesc = {};
  bindGroupDesc.entries = bindGroupEntries.data();
  bindGroupDesc.entryCount = bindGroupEntries.size();
  bindGroupDesc.layout =
      wgpuComputePipelineGetBindGroupLayout(m_ComputePipeline, 0);

  m_BindGroup = wgpuDeviceCreateBindGroup(m_Device.value(), &bindGroupDesc);
  wgpuBindGroupLayoutRelease(bindGroupDesc.layout);
}

WebGPUComputePipeline::~WebGPUComputePipeline() {
  wgpuBindGroupRelease(m_BindGroup);
  wgpuComputePipelineRelease(m_ComputePipeline);
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

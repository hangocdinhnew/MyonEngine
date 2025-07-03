// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUUtils.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUAPI.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
WebGPUAPI::WebGPUAPI(SDL_Window *m_Window, std::string &title,
                     std::string &computeFolderName,
                     std::string &computeFileName) {
  // WebGPU Instance
  m_WebGPUInstance = std::make_unique<WebGPUInstance>();

  // WebGPU Surface
  m_WebGPUSurfaceConfig = WebGPUSurfaceConfig{
      .p_Instance = m_WebGPUInstance->getInstance(), .p_Window = m_Window};
  m_WebGPUSurface = std::make_unique<WebGPUSurface>(m_WebGPUSurfaceConfig);

  // WebGPU Adapter
  m_WebGPUAdapterConfig =
      WebGPUAdapterConfig{.p_Instance = m_WebGPUInstance->getInstance(),
                          .p_Surface = m_WebGPUSurface->getSurface()};
  m_WebGPUAdapter = std::make_unique<WebGPUAdapter>(m_WebGPUAdapterConfig);

  // WebGPU Device
  m_WebGPUDeviceConfig = WebGPUDeviceConfig{
      .p_Name = title,
      .p_Instance = m_WebGPUInstance->getInstance(),
      .p_Adapter = m_WebGPUAdapter->getAdapter(),
  };
  m_WebGPUDevice = std::make_unique<WebGPUDevice>(m_WebGPUDeviceConfig);

  // WebGPU Buffer
  m_WebGPUBufferConfig =
      WebGPUBufferConfig{.p_Device = m_WebGPUDevice->getDevice()};
  m_WebGPUBuffer = std::make_unique<WebGPUBuffer>(m_WebGPUBufferConfig);

  // Compute Pipeline
  m_WebGPUComputePipelineConfig = WebGPUComputePipelineConfig{
      .p_Device = m_WebGPUDevice->getDevice(),
      .p_InputBuffer = m_WebGPUBuffer->getInputBuffer(),
      .p_OutputBuffer = m_WebGPUBuffer->getOutputBuffer(),
      .p_FolderName = computeFolderName,
      .p_FilePath = computeFileName};
  m_WebGPUComputePipeline =
      std::make_unique<WebGPUComputePipeline>(m_WebGPUComputePipelineConfig);

  // WebGPU Command Queue
  m_WebGPUCommandQueueConfig = WebGPUCommandQueueConfig{
      .p_Instance = m_WebGPUInstance->getInstance(),
      .p_Device = m_WebGPUDevice->getDevice(),
      .p_OutputBuffer = m_WebGPUBuffer->getOutputBuffer(),
      .p_StagingBuffer = m_WebGPUBuffer->getStagingBuffer(),
      .p_OutputBufferDesc = m_WebGPUBuffer->getOutputBufferDesc(),
      .p_StagingBufferDesc = m_WebGPUBuffer->getStagingBufferDesc(),
      .p_ComputePipeline = m_WebGPUComputePipeline->getComputePipeline(),
      .p_BindGroup = m_WebGPUComputePipeline->getBindGroup()};
  m_WebGPUCommandQueue =
      std::make_unique<WebGPUCommandQueue>(m_WebGPUCommandQueueConfig);

  m_WebGPUSurface->configureSurface(m_WebGPUAdapter->getAdapter(),
                                    m_WebGPUDevice->getDevice());
}

WebGPUAPI::~WebGPUAPI() {
  MYON_CORE_INFO("Shutting down WebGPU...");

  m_WebGPUSurface->unconfigureSurface();
}

void WebGPUAPI::FetchComputeBufferDataSync() {
  fetchBufferDataSync(
      m_WebGPUInstance->getInstance(), m_WebGPUBuffer->getStagingBuffer(),
      [&](const void *data) {
        const float *floatData = static_cast<const float *>(data);

#if defined(MYON_DEBUG)
        MYON_CORE_INFO("WebGPU - Result: [");
        for (size_t i = 0; i < ELEMENT_COUNT * sizeof(float); i++) {
          if (i > 0)
            MYON_CORE_INFO("WebGPU - ,");
          MYON_CORE_INFO("WebGPU - {}", floatData[i]);
        }
        MYON_CORE_INFO("WebGPU - ]");
#endif
      });
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

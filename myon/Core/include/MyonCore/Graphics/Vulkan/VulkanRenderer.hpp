#pragma once

// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"
#include <vulkan/vulkan.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
struct VulkanRendererConfig {
  vk::Device p_Device;
  vk::Queue p_GraphicsQueue;
  vk::Queue p_PresentQueue;
  vk::SwapchainKHR p_SwapChain;
  std::vector<vk::CommandBuffer> p_CommandBuffers;
  vk::RenderPass p_RenderPass;
  vk::PipelineLayout p_PipelineLayout;
  vk::Pipeline p_GraphicsPipeline;
  vk::Extent2D p_SwapChainExtent;
  std::vector<vk::Framebuffer> p_SwapChainFramebuffers;
  std::vector<vk::Semaphore> p_ImageAvailableSemaphores;
  std::vector<vk::Semaphore> p_RenderFinishedSemaphores;
  std::vector<vk::Fence> p_InFlightFences;
  vk::Buffer p_VertexBuffer;
  vk::Buffer p_IndexBuffer;
  std::vector<void *> p_UniformBuffersMapped;
  std::vector<vk::DescriptorSet> p_DescriptorSets;
};

class VulkanRenderer {
public:
  VulkanRenderer(VulkanRendererConfig &p_RendererConfig);
  ~VulkanRenderer() = default;

  void UpdateUniformBuffer();

  void DrawFrame();

  void UpdateSwapchain(VulkanRendererConfig &p_RendererConfig);

  bool &ShouldRecreateSwapChain() { return m_ShouldRecreateSwapChain; };

  void ResetShouldRecreateSwapChain() { m_ShouldRecreateSwapChain = false; };

private:
  vk::Device &m_Device;

  std::vector<vk::CommandBuffer> m_CommandBuffers;
  vk::RenderPass m_RenderPass;
  vk::PipelineLayout m_PipelineLayout;
  vk::Pipeline m_GraphicsPipeline;
  vk::SwapchainKHR m_SwapChain;
  vk::Queue m_GraphicsQueue;
  vk::Queue m_PresentQueue;

  std::vector<vk::Semaphore> m_ImageAvailableSemaphores;
  std::vector<vk::Semaphore> m_RenderFinishedSemaphores;
  std::vector<vk::Fence> m_InFlightFences;

  vk::Extent2D m_SwapChainExtent;
  std::vector<vk::Framebuffer> m_SwapChainFramebuffers;

  vk::Buffer m_VertexBuffer;
  vk::Buffer m_IndexBuffer;

  std::vector<void *> m_UniformBuffersMapped;
  std::vector<vk::DescriptorSet> m_DescriptorSets;

  void recordCommandBuffer(uint32_t imageIndex);

  uint32_t m_CurrentFrame = 0;

  bool m_ShouldRecreateSwapChain = false;
};
} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

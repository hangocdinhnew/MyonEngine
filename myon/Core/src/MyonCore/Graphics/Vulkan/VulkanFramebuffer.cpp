#include "MyonCore/Graphics/Vulkan/VulkanFramebuffer.hpp"

namespace MyonCore {
VulkanFramebuffer::VulkanFramebuffer(
    vk::Device &p_Device, vk::RenderPass &p_RenderPass,
    std::vector<vk::ImageView> &p_SwapChainImageViews,
    vk::Extent2D &p_SwapChainExtent)
    : m_Device(p_Device) {
  m_SwapchainFramebuffers.resize(p_SwapChainImageViews.size());

  for (size_t i = 0; i < p_SwapChainImageViews.size(); i++) {
    vk::ImageView attachments[] = {p_SwapChainImageViews[i]};

    vk::FramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = vk::StructureType::eFramebufferCreateInfo;
    framebufferInfo.renderPass = p_RenderPass;
    framebufferInfo.attachmentCount = 1;
    framebufferInfo.pAttachments = attachments;
    framebufferInfo.width = p_SwapChainExtent.width;
    framebufferInfo.height = p_SwapChainExtent.height;
    framebufferInfo.layers = 1;

    if (m_Device.createFramebuffer(&framebufferInfo, nullptr,
                                   &m_SwapchainFramebuffers[i]) !=
        vk::Result::eSuccess) {
      MYON_DO_CORE_ASSERT("Failed to create a framebuffer!");
    }
  }
}

VulkanFramebuffer::~VulkanFramebuffer() {
  for (auto framebuffer : m_SwapchainFramebuffers) {
    m_Device.destroyFramebuffer(framebuffer, nullptr);
  }
}

void VulkanFramebuffer::cleanup() {
  for (auto framebuffer : m_SwapchainFramebuffers) {
    m_Device.destroyFramebuffer(framebuffer, nullptr);
  }
}

} // namespace MyonCore

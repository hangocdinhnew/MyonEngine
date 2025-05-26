#include "MyonCore/Graphics/Vulkan/VulkanRenderPass.hpp"

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
VulkanRenderPass::VulkanRenderPass(VulkanRenderPassConfig &p_RenderPassConfig)
    : m_Device(p_RenderPassConfig.p_Device) {
  vk::AttachmentDescription colorAttachment{};
  colorAttachment.format = p_RenderPassConfig.p_SwapchainImageFormat;
  colorAttachment.samples = vk::SampleCountFlagBits::e1;
  colorAttachment.loadOp = vk::AttachmentLoadOp::eClear;
  colorAttachment.storeOp = vk::AttachmentStoreOp::eStore;
  colorAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
  colorAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
  colorAttachment.initialLayout = vk::ImageLayout::eUndefined;
  colorAttachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;

  vk::AttachmentReference colorAttachmentRef{};
  colorAttachmentRef.attachment = 0;
  colorAttachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

  vk::SubpassDescription subpass{};
  subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments = &colorAttachmentRef;

  vk::RenderPassCreateInfo renderPassInfo{};
  renderPassInfo.sType = vk::StructureType::eRenderPassCreateInfo;
  renderPassInfo.attachmentCount = 1;
  renderPassInfo.pAttachments = &colorAttachment;
  renderPassInfo.subpassCount = 1;
  renderPassInfo.pSubpasses = &subpass;

  if (m_Device.createRenderPass(&renderPassInfo, nullptr, &m_RenderPass) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to create render pass!");
  }
}

VulkanRenderPass::~VulkanRenderPass() {
  m_Device.destroyRenderPass(m_RenderPass, nullptr);
}

void VulkanRenderPass::cleanup() {
  m_Device.destroyRenderPass(m_RenderPass, nullptr);
}
} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

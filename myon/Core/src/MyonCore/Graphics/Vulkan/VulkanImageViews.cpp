#include "MyonCore/Graphics/Vulkan/VulkanImageViews.hpp"

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
VulkanImageViews::VulkanImageViews(VulkanImageViewsConfig &p_ImageViewsConfig)
    : m_Device(p_ImageViewsConfig.p_Device) {
  m_SwapChainImageViews.resize(p_ImageViewsConfig.p_SwapChainImages.size());

  for (size_t i = 0; i < p_ImageViewsConfig.p_SwapChainImages.size(); i++) {
    vk::ImageViewCreateInfo createInfo{};
    createInfo.sType = vk::StructureType::eImageViewCreateInfo;
    createInfo.image = p_ImageViewsConfig.p_SwapChainImages[i];

    createInfo.viewType = vk::ImageViewType::e2D;
    createInfo.format = p_ImageViewsConfig.p_SwapChainImageFormat;

    createInfo.components.r = vk::ComponentSwizzle::eIdentity;
    createInfo.components.g = vk::ComponentSwizzle::eIdentity;
    createInfo.components.b = vk::ComponentSwizzle::eIdentity;
    createInfo.components.a = vk::ComponentSwizzle::eIdentity;

    createInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    if (m_Device.createImageView(&createInfo, nullptr,
                                 &m_SwapChainImageViews[i]) !=
        vk::Result::eSuccess) {
      MYON_DO_CORE_ASSERT("Failed to create image views!");
    }
  }
}

VulkanImageViews::~VulkanImageViews() {
  for (auto imageView : m_SwapChainImageViews) {
    vkDestroyImageView(m_Device, imageView, nullptr);
  }
}

void VulkanImageViews::cleanup() {
  for (auto imageView : m_SwapChainImageViews) {
    vkDestroyImageView(m_Device, imageView, nullptr);
  }
}
}
}
} // namespace MyonCore

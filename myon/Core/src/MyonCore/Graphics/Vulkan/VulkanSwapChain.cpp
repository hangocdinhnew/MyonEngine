#include "MyonCore/Graphics/Vulkan/VulkanSwapChain.hpp"

namespace MyonCore {

VulkanSwapChain::VulkanSwapChain(SDL_Window *p_Window,
                                 vk::PhysicalDevice p_PhysicalDevice,
                                 vk::Device p_Device, vk::SurfaceKHR p_Surface)
    : m_PhysicalDevice(p_PhysicalDevice), m_Window(p_Window),
      m_Device(p_Device), m_Surface(p_Surface) {
  SwapChainSupportDetails swapChainSupport =
      Vulkan_QuerySwapChainSupport(m_PhysicalDevice, m_Surface);

  vk::SurfaceFormatKHR surfaceFormat =
      chooseSwapSurfaceFormat(swapChainSupport.formats);
  vk::PresentModeKHR presentMode =
      chooseSwapPresentMode(swapChainSupport.presentModes);
  vk::Extent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

  uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
  if (swapChainSupport.capabilities.maxImageCount > 0 &&
      imageCount > swapChainSupport.capabilities.maxImageCount) {
    imageCount = swapChainSupport.capabilities.maxImageCount;
  }

  vk::SwapchainCreateInfoKHR createInfo{};
  createInfo.sType = vk::StructureType::eSwapchainCreateInfoKHR;
  createInfo.surface = m_Surface;
  createInfo.minImageCount = imageCount;
  createInfo.imageFormat = surfaceFormat.format;
  createInfo.imageColorSpace = surfaceFormat.colorSpace;
  createInfo.imageExtent = extent;
  createInfo.imageArrayLayers = 1;
  createInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;

  QueueFamilyIndices indices =
      Vulkan_FindQueueFamilies(p_PhysicalDevice, m_Surface);
  uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(),
                                   indices.presentFamily.value()};

  if (indices.graphicsFamily != indices.presentFamily) {
    createInfo.imageSharingMode = vk::SharingMode::eConcurrent;
    createInfo.queueFamilyIndexCount = 2;
    createInfo.pQueueFamilyIndices = queueFamilyIndices;
  } else {
    createInfo.imageSharingMode = vk::SharingMode::eExclusive;
    createInfo.queueFamilyIndexCount = 0;     // Optional
    createInfo.pQueueFamilyIndices = nullptr; // Optional
  }

  createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
  createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
  createInfo.presentMode = presentMode;
  createInfo.clipped = vk::True;
  createInfo.oldSwapchain = nullptr;

  if (m_Device.createSwapchainKHR(&createInfo, nullptr, &m_SwapChain) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to create Swap chain!");
  }

  m_Device.getSwapchainImagesKHR(m_SwapChain, &imageCount, nullptr);
  swapChainImages.resize(imageCount);
  m_Device.getSwapchainImagesKHR(m_SwapChain, &imageCount,
                                 swapChainImages.data());

  swapChainImageFormat = surfaceFormat.format;
  swapChainExtent = extent;
}

VulkanSwapChain::~VulkanSwapChain() {
  m_Device.destroySwapchainKHR(m_SwapChain, nullptr);
}

void VulkanSwapChain::cleanup() {
  m_Device.destroySwapchainKHR(m_SwapChain, nullptr);
}

vk::SurfaceFormatKHR VulkanSwapChain::chooseSwapSurfaceFormat(
    const std::vector<vk::SurfaceFormatKHR> &availableFormats) {
  for (const auto &availableFormat : availableFormats) {
    if (availableFormat.format == vk::Format::eB8G8R8A8Srgb &&
        availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
      return availableFormat;
    }
  }

  return availableFormats[0];
}

vk::PresentModeKHR VulkanSwapChain::chooseSwapPresentMode(
    const std::vector<vk::PresentModeKHR> &availablePresentModes) {
  for (const auto &availablePresentMode : availablePresentModes) {
    if (availablePresentMode == vk::PresentModeKHR::eMailbox) {
      return availablePresentMode;
    }
  }

  return vk::PresentModeKHR::eFifo;
}

vk::Extent2D VulkanSwapChain::chooseSwapExtent(
    const vk::SurfaceCapabilitiesKHR &capabilities) {
  if (capabilities.currentExtent.width !=
      std::numeric_limits<uint32_t>::max()) {
    return capabilities.currentExtent;
  } else {
    int width, height;
    SDL_GetWindowSize(m_Window, &width, &height);

    vk::Extent2D actualExtent = {static_cast<uint32_t>(width),
                                 static_cast<uint32_t>(height)};

    actualExtent.width =
        std::clamp(actualExtent.width, capabilities.minImageExtent.width,
                   capabilities.maxImageExtent.width);
    actualExtent.height =
        std::clamp(actualExtent.height, capabilities.minImageExtent.height,
                   capabilities.maxImageExtent.height);

    return actualExtent;
  }
}

} // namespace MyonCore

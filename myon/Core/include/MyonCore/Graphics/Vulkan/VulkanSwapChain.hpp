#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

namespace MyonCore {
struct VulkanSwapChainConfig {
  SDL_Window *p_Window;
  vk::PhysicalDevice p_PhysicalDevice;
  vk::Device p_Device;
  vk::SurfaceKHR p_Surface;
};

class VulkanSwapChain {
public:
  VulkanSwapChain(VulkanSwapChainConfig& p_SwapChainConfig);
  ~VulkanSwapChain();

  std::vector<vk::Image> &getSwapChainImages() { return swapChainImages; }

  vk::Format &getSwapChainImageFormat() { return swapChainImageFormat; }

  vk::Extent2D &getSwapChainExtent() { return swapChainExtent; }

  vk::SwapchainKHR &getSwapChain() { return m_SwapChain; }

  void cleanup();

private:
  vk::SwapchainKHR m_SwapChain;

  SDL_Window *m_Window;
  vk::PhysicalDevice &m_PhysicalDevice;
  vk::Device &m_Device;
  vk::SurfaceKHR &m_Surface;

  std::vector<vk::Image> swapChainImages;
  vk::Format swapChainImageFormat;
  vk::Extent2D swapChainExtent;

  vk::SurfaceFormatKHR chooseSwapSurfaceFormat(
      const std::vector<vk::SurfaceFormatKHR> &availableFormats);
  vk::PresentModeKHR chooseSwapPresentMode(
      const std::vector<vk::PresentModeKHR> &availablePresentModes);
  vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR &capabilities);
};
} // namespace MyonCore

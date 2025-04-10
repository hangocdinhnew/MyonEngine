#include "MyonCore/Core/Log.hpp"
#include <vulkan/vulkan.hpp>

namespace MyonCore {
class VulkanImageViews {
public:
  VulkanImageViews(vk::Device p_Device, std::vector<vk::Image> p_SwapChainImages, vk::Format p_SwapChainImageFormat);
  ~VulkanImageViews();

  std::vector<vk::ImageView> getSwapChainImageViews() {
    return m_SwapChainImageViews;
  }

private:
  vk::Device m_Device;

  std::vector<vk::ImageView> m_SwapChainImageViews;
};
} // namespace MyonCore

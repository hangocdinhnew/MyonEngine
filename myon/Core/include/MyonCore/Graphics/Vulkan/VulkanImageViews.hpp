#include "MyonCore/Core/Log.hpp"
#include <vulkan/vulkan.hpp>

namespace MyonCore {
struct VulkanImageViewsConfig {
  vk::Device p_Device;
  std::vector<vk::Image> p_SwapChainImages;
  vk::Format p_SwapChainImageFormat;
};

class VulkanImageViews {
public:
  VulkanImageViews(VulkanImageViewsConfig &p_ImageViewsConfig);
  ~VulkanImageViews();

  std::vector<vk::ImageView> &getSwapChainImageViews() {
    return m_SwapChainImageViews;
  }

  void cleanup();

private:
  vk::Device &m_Device;

  std::vector<vk::ImageView> m_SwapChainImageViews;
};
} // namespace MyonCore

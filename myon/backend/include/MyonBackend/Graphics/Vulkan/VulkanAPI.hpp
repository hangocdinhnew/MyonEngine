// clang-format off
#include "MyonBackend/Graphics/Vulkan/VulkanInstance.hpp"
#include "MyonBackend/Graphics/Vulkan/VulkanValidationLayer.hpp"
#include "MyonBackend/Graphics/Vulkan/VulkanDevice.hpp"
// clang-format on

namespace MyonBackend {
class VulkanAPI {
public:
  VulkanAPI(const std::string &title);
  ~VulkanAPI();

private:
  std::unique_ptr<VulkanInstance> m_Instance;
  std::unique_ptr<VulkanValidationLayer> m_ValidationLayer;
  std::unique_ptr<VulkanDevice> m_VulkanDevice;
};
} // namespace MyonBackend

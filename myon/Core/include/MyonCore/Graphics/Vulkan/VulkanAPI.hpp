// clang-format off
#include "MyonCore/Graphics/Vulkan/VulkanInstance.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanValidationLayer.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanDevice.hpp"
// clang-format on

namespace MyonCore {
class VulkanAPI {
public:
  VulkanAPI(const std::string &title);
  ~VulkanAPI();

private:
  std::unique_ptr<VulkanInstance> m_Instance;
  std::unique_ptr<VulkanValidationLayer> m_ValidationLayer;
  std::unique_ptr<VulkanDevice> m_VulkanDevice;
};
} // namespace MyonCore

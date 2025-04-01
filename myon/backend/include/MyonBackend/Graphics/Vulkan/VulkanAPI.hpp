#include "MyonBackend/Graphics/Vulkan/VulkanInstance.hpp"
#include "MyonBackend/Graphics/Vulkan/VulkanValidationLayer.hpp"

namespace MyonBackend {
class VulkanAPI {
public:
  VulkanAPI(const std::string &title);
  ~VulkanAPI();

private:
  std::unique_ptr<VulkanInstance> m_Instance;
  std::unique_ptr<VulkanValidationLayer> m_ValidationLayer;
};
} // namespace MyonBackend

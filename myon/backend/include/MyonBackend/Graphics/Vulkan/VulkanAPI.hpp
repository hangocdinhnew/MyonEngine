#include "MyonBackend/Graphics/Vulkan/VulkanInstance.hpp"
#include "MyonBackend/Graphics/Vulkan/VulkanValidationLayer.hpp"

namespace MyonBackend {
class VulkanAPI {
public:
  VulkanAPI(const std::string &title);
  ~VulkanAPI();

private:
  VulkanInstance *m_Instance;
  VulkanValidationLayer *m_ValidationLayer;
};
} // namespace MyonBackend

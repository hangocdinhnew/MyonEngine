#include "MyonBackend/Core/Log.hpp"
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include <set>

namespace MyonBackend {
class VulkanInstance {
public:
  VulkanInstance(const std::string &title);
  ~VulkanInstance();

private:
  vk::Instance instance;
};
} // namespace MyonBackend

#pragma once
// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"
#include <SDL3/SDL_vulkan.h>
#include <set>
#include <vulkan/vulkan.hpp>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
struct VulkanInstanceConfig {
  std::string title;
};

class VulkanInstance {
public:
  VulkanInstance(VulkanInstanceConfig &p_InstanceConfig);
  ~VulkanInstance();

  vk::Instance &getInstance() { return m_Instance; }

private:
  vk::Instance m_Instance;

  const std::string title;

  std::vector<const char *> getRequiredExtensions();

  bool checkValidationLayerSupport();
};
} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

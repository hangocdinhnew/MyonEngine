#pragma once
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"
#include <SDL3/SDL_vulkan.h>
#include <set>
#include <vulkan/vulkan.hpp>

namespace MyonCore {
class VulkanInstance {
public:
  VulkanInstance(const std::string &title);
  ~VulkanInstance();

  vk::Instance& getInstance() { return m_Instance; }

private:
  vk::Instance m_Instance;

  std::vector<const char *> getRequiredExtensions();

  bool checkValidationLayerSupport();
};
} // namespace MyonCore

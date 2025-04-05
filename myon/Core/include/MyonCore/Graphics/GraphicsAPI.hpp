#pragma once
#include "MyonCore/Graphics/Vulkan/VulkanAPI.hpp"

namespace MyonCore {
class GraphicsAPI {
public:
  GraphicsAPI(const std::string &title);
  ~GraphicsAPI() = default;

private:
  std::unique_ptr<VulkanAPI> m_VulkanAPI;
};
} // namespace MyonCore

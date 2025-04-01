#pragma once
#include "MyonBackend/Graphics/Vulkan/VulkanAPI.hpp"

namespace MyonBackend {
class GraphicsAPI {
public:
  GraphicsAPI(const std::string &title);
  ~GraphicsAPI() = default;

private:
  std::unique_ptr<VulkanAPI> m_VulkanAPI;
};
} // namespace MyonBackend

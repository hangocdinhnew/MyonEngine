#pragma once
#include "MyonBackend/Graphics/Vulkan/VulkanAPI.hpp"

namespace MyonBackend {
class GraphicsAPI {
public:
  GraphicsAPI(const std::string &title);
  ~GraphicsAPI();

private:
  VulkanAPI* m_VulkanAPI;
};
} // namespace MyonBackend

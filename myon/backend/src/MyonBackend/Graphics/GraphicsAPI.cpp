#include "MyonBackend/Graphics/GraphicsAPI.hpp"

namespace MyonBackend {
GraphicsAPI::GraphicsAPI(const std::string &title) {
  m_VulkanAPI = std::make_unique<VulkanAPI>(title);
}
}

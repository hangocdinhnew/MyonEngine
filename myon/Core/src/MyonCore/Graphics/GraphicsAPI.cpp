#include "MyonCore/Graphics/GraphicsAPI.hpp"

namespace MyonCore {
GraphicsAPI::GraphicsAPI(const std::string &title) {
  m_VulkanAPI = std::make_unique<VulkanAPI>(title);
}
}

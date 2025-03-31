#include "MyonBackend/Graphics/GraphicsAPI.hpp"

namespace MyonBackend {
GraphicsAPI::GraphicsAPI(const std::string &title) {
  m_VulkanAPI = new VulkanAPI(title);
}

GraphicsAPI::~GraphicsAPI() {
  delete m_VulkanAPI;
}
}

#include "MyonCore/Graphics/GraphicsAPI.hpp"

namespace MyonCore {
namespace Graphics {
GraphicsAPI::GraphicsAPI(std::string &name) {
  m_WebGPUAPI = std::make_unique<WebGPU::WebGPUAPI>(name);
}
} // namespace Graphics
} // namespace MyonCore

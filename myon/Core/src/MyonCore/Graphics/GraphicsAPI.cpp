#include "MyonCore/Graphics/GraphicsAPI.hpp"

namespace MyonCore {
namespace Graphics {
GraphicsAPI::GraphicsAPI() {
  m_WebGPUAPI = std::make_unique<WebGPU::WebGPUAPI>();
}
} // namespace Graphics
} // namespace MyonCore

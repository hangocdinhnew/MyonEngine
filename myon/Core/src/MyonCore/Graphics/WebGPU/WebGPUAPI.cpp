// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUAPI.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
WebGPUAPI::WebGPUAPI() {
  m_WebGPUInstance = std::make_unique<WebGPUInstance>();
}

WebGPUAPI::~WebGPUAPI() { MYON_CORE_INFO("Shutting down WebGPU..."); }
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

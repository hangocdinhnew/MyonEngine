#pragma once

// clang-format off
#include "MyonCore/Graphics/WebGPU/WebGPUAPI.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
class GraphicsAPI {
public:
  GraphicsAPI(SDL_Window *m_Window, std::string &title, std::string& computeFolderName, std::string& computeFileName);
  ~GraphicsAPI() = default;

  void PollDevice() { m_WebGPUAPI->PollDevices(); }

  void FetchComputeBufferDataSync() {
    m_WebGPUAPI->FetchComputeBufferDataSync();
  }

private:
  std::unique_ptr<WebGPU::WebGPUAPI> m_WebGPUAPI;
};
} // namespace Graphics
} // namespace MyonCore

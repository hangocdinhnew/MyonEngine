#pragma once

// clang-format off
#include "MyonCore/Graphics/WebGPU/WebGPUAPI.hpp"
#include "MyonCore/RHI/RHI.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
class GraphicsAPI {
public:
  GraphicsAPI(SDL_Window *m_Window, std::string &title,
              MyonRHI::GPUBackend p_Backend);
  ~GraphicsAPI() = default;

  void PollDevice() { m_WebGPUAPI->PollDevices(); }

  MyonRHI::GPUDevice &getDevice();
  MyonRHI::GPUQueue &getQueue();
  MyonRHI::GPUSurface &getSurface();

private:
  MyonRHI::GPUDevice m_Device{};
  MyonRHI::GPUQueue m_Queue{};
  MyonRHI::GPUSurface m_Surface{};

  MyonRHI::GPUBackend m_Backend{};

  std::unique_ptr<WebGPU::WebGPUAPI> m_WebGPUAPI;
};
} // namespace Graphics
} // namespace MyonCore

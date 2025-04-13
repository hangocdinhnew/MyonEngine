#include "MyonCore/Core/Log.hpp"
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

namespace MyonCore {
class VulkanSurface {
public:
  VulkanSurface(SDL_Window *p_Window, vk::Instance &p_Instance);
  ~VulkanSurface();

  vk::SurfaceKHR &getSurface() { return m_Surface; }

private:
  SDL_Window *m_Window;

  vk::Instance &m_Instance;
  vk::SurfaceKHR m_Surface;
};
} // namespace MyonCore

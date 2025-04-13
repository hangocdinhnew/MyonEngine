#pragma once

// clang-format off
#include "MyonCore/Core/Log.hpp"

#include <fstream>
#include <shaderc/shaderc.hpp>
#include <vulkan/vulkan.hpp>
#include <glm/glm.hpp>
// clang-format on

namespace MyonCore {
struct Vertex {
  glm::vec2 pos;
  glm::vec3 color;

  static vk::VertexInputBindingDescription getBindingDescription() {
    vk::VertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex);
    bindingDescription.inputRate = vk::VertexInputRate::eVertex;

    return bindingDescription;
  }

  static std::array<vk::VertexInputAttributeDescription, 2>
  getAttributeDescriptions() {
    std::array<vk::VertexInputAttributeDescription, 2> attributeDescriptions{};

    attributeDescriptions[0].binding = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = vk::Format::eR32G32Sfloat;
    attributeDescriptions[0].offset = offsetof(Vertex, pos);

    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = vk::Format::eR32G32B32Sfloat;
    attributeDescriptions[1].offset = offsetof(Vertex, color);

    return attributeDescriptions;
  }
};

class VulkanGraphicsPipeline {
public:
  VulkanGraphicsPipeline(vk::Device p_Device, vk::RenderPass p_RenderPass,
                         const std::string vert, const std::string frag);
  ~VulkanGraphicsPipeline();

  vk::Pipeline getGraphicsPipeline() { return m_GraphicsPipeline; }

  void cleanup();

private:
  vk::Device m_Device;

  std::string readFile(const std::string &filename);
  static std::vector<uint32_t> compileGLSL(const std::string &source,
                                           shaderc_shader_kind kind,
                                           const std::string &name = "shader");

  vk::ShaderModule createShaderModule(const std::vector<uint32_t> &code);

  vk::PipelineLayout m_PipelineLayout;
  vk::Pipeline m_GraphicsPipeline;
};
} // namespace MyonCore

# Set some stuff and do stuff
project(MyonCore LANGUAGES CXX C)

set(MyonCore_SOURCES
    "src/MyonCore/Core/Log.cpp"
    "src/MyonCore/Layers/LayerStack.cpp"
    "src/MyonCore/Core/Engine.cpp"
    "src/MyonCore/Core/Window.cpp"
    "src/MyonCore/Utils/MyonVMAImpl.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanInstance.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanValidationLayer.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanSurface.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanDevice.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanAllocator.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanSwapChain.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanImageViews.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanRenderPass.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanDescriptorSetLayout.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanGraphicsPipeline.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanFramebuffer.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanCommandBuffers.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanBuffer.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanDescriptorPool.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanDescriptorSets.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanSyncObjects.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanRenderer.cpp"
    "src/MyonCore/Graphics/Vulkan/VulkanAPI.cpp"
    "src/MyonCore/Graphics/GraphicsAPI.cpp")

# Make the library
add_library(MyonCore STATIC "${MyonCore_SOURCES}")
target_include_directories(MyonCore PUBLIC "include/")

# Definitions
if(CMAKE_BUILD_TYPE MATCHES "Debug")
  target_compile_definitions(MyonCore PUBLIC MYON_DEBUG)
endif()

# Link libraries
target_link_libraries(MyonCore PUBLIC spdlog::spdlog)
target_link_libraries(MyonCore PUBLIC SDL3::SDL3)

target_link_libraries(MyonCore PUBLIC glslang::glslang SPIRV-Tools-opt SPIRV-Tools Vulkan::Vulkan
                                                          unofficial::shaderc::shaderc glm::glm
                                                          GPUOpen::VulkanMemoryAllocator
                                                          VulkanMemoryAllocator-Hpp::VulkanMemoryAllocator-Hpp)

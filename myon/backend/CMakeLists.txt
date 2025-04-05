# Set some stuff and do stuff
project(MyonBackend LANGUAGES CXX C)

set(MyonBackend_SOURCES
    "src/MyonBackend/Core/Log.cpp"
    "src/MyonBackend/Core/Engine.cpp"
    "src/MyonBackend/Core/Window.cpp"
    "src/MyonBackend/Graphics/Vulkan/VulkanInstance.cpp"
    "src/MyonBackend/Graphics/Vulkan/VulkanValidationLayer.cpp"
    "src/MyonBackend/Graphics/Vulkan/VulkanDevice.cpp"
    "src/MyonBackend/Graphics/Vulkan/VulkanAPI.cpp"
    "src/MyonBackend/Graphics/GraphicsAPI.cpp")

# Make the library
add_library(MyonBackend STATIC "${MyonBackend_SOURCES}")
target_include_directories(MyonBackend PUBLIC "include/")

# Definitions
if(CMAKE_BUILD_TYPE MATCHES "Debug")
  target_compile_definitions(MyonBackend PUBLIC MYON_DEBUG)
endif()

# Link libraries
target_link_libraries(MyonBackend PUBLIC Vulkan::Headers)
target_link_libraries(MyonBackend PUBLIC vulkan)

target_link_libraries(MyonBackend PUBLIC spdlog::spdlog)
target_link_libraries(MyonBackend PUBLIC glfw)

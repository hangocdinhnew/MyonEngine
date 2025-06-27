# Set some stuff and do stuff
project(MyonCore LANGUAGES CXX C)

set(MyonCore_SOURCES
    "src/MyonCore/Core/Log.cpp"
    "src/MyonCore/Layers/LayerStack.cpp"
    "src/MyonCore/Core/Engine.cpp"
    "src/MyonCore/Core/Window.cpp"
    "src/MyonCore/Graphics/WebGPU/WebGPUInstance.cpp"
    "src/MyonCore/Graphics/WebGPU/WebGPUSurface.cpp"
    "src/MyonCore/Graphics/WebGPU/WebGPUAdapter.cpp"
    "src/MyonCore/Graphics/WebGPU/WebGPUDevice.cpp"
    "src/MyonCore/Graphics/WebGPU/WebGPUAPI.cpp"
    "src/MyonCore/Graphics/WebGPU/WebGPUCommandQueue.cpp"
    "src/MyonCore/Graphics/GraphicsAPI.cpp")

# Make the library
add_library(MyonCore STATIC "${MyonCore_SOURCES}")
target_include_directories(MyonCore PUBLIC "include/")

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  set(SANITIZE_FLAGS "-fsanitize=address" "-fno-omit-frame-pointer")

  target_compile_options(MyonCore PRIVATE ${SANITIZE_FLAGS})
  target_link_options(MyonCore PRIVATE ${SANITIZE_FLAGS})
endif()

# Definitions
if(CMAKE_BUILD_TYPE MATCHES "Debug")
  target_compile_definitions(MyonCore PUBLIC MYON_DEBUG)
endif()

# Link libraries
target_link_libraries(MyonCore PUBLIC spdlog::spdlog)
target_link_libraries(MyonCore PUBLIC SDL3::SDL3)

target_link_libraries(MyonCore PUBLIC webgpu sdl3webgpu)

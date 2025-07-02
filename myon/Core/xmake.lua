target("MyonCore")
    set_kind("shared")
    set_languages("cxx20")

    add_includedirs("include", {public = true})

    add_deps("sdl3webgpu", {public = true})

    add_packages("wgpu-native", {public = true})
    add_packages("libsdl3", {public = true})
    add_packages("glm", {public = true})
    add_packages("spdlog", {public = true})

    add_files(
        "src/MyonCore/Core/Log.cpp",
        "src/MyonCore/Layers/LayerStack.cpp",
        "src/MyonCore/Core/Engine.cpp",
        "src/MyonCore/Core/Window.cpp",
        "src/MyonCore/Graphics/WebGPU/WebGPUUtils.cpp",
        "src/MyonCore/Graphics/WebGPU/WebGPUInstance.cpp",
        "src/MyonCore/Graphics/WebGPU/WebGPUSurface.cpp",
        "src/MyonCore/Graphics/WebGPU/WebGPUAdapter.cpp",
        "src/MyonCore/Graphics/WebGPU/WebGPUDevice.cpp",
        "src/MyonCore/Graphics/WebGPU/WebGPUBuffer.cpp",
        "src/MyonCore/Graphics/WebGPU/WebGPUCommandQueue.cpp",
        "src/MyonCore/Graphics/WebGPU/WebGPUComputePipeline.cpp",
        "src/MyonCore/Graphics/WebGPU/WebGPUAPI.cpp",
        "src/MyonCore/Graphics/GraphicsAPI.cpp"
    )

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
        "src/**/*.cpp"
    )

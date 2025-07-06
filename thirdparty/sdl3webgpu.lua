target("sdl3webgpu")
    set_kind("shared")
    add_files("sdl3webgpu/sdl3webgpu.c")
    add_includedirs("sdl3webgpu", {public = true})

    add_packages("wgpu-native", {public = true})
    add_packages("libsdl3", {public = true})

    if is_plat("macosx") then
        add_cxflags("-x", "objective-c", {force = true})

        add_frameworks("CoreVideo", "IOKit", "QuartzCore", "Cocoa")
    end

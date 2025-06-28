set_project("Myon")
set_version("0.1")

add_rules("mode.debug", "mode.release")

on_config(function (target)
        if (target:has_tool("cxx", "cl")) then
		target:add("cxxflags", "/utf-8")
        end
end)

set_languages("cxx20")

if is_mode("debug") or is_mode("asan") then
  set_policy("build.sanitizer.address", true)
  add_defines("MYON_DEBUG")
end

add_requires("wgpu-native")
add_requires("libsdl3")
add_requires("glm")
add_requires("spdlog")

includes("myon/Core", "myon/Sandbox", "thirdparty/sdl3webgpu.lua")

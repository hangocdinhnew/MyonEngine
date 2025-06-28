set_project("Myon")
set_version("0.1")

add_rules("mode.debug", "mode.release")

set_languages("cxx20")

if is_plat("windows") and not is_tool("msvc") then
  add_ldflags("-static", { force = true })
end

if is_mode("debug") or is_mode("asan") then
  set_policy("build.sanitizer.address", true)
  add_defines("MYON_DEBUG")
end

add_requires("wgpu-native")
add_requires("libsdl3 master")
add_requires("glm master")
add_requires("spdlog master")

includes("myon/Core", "myon/Sandbox", "thirdparty/sdl3webgpu.lua")

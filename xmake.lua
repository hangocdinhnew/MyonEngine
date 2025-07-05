set_project("Myon")
set_version("0.1")

add_rules("mode.debug", "mode.release")

after_config(function(target)
  if (target:has_tool("cxx", "cl")) then
    target:add("cxxflags", "/utf-8")
  end
end)

set_languages("cxx23")

if is_mode("debug") then
  set_policy("build.sanitizer.address", true)
  add_defines("MYON_DEBUG")
end

add_requires("wgpu-native")
add_requires("libsdl3")
add_requires("glm")
add_requires("spdlog")

option("enable_logtofile")
  set_default(false)
  set_showmenu(true)
  set_description("Enable spdlog to log to a file (by default Myon.log)")
  add_defines("LOGTOFILE")
option_end()

add_options("enable_logtofile")

includes("myon/Core", "myon/Sandbox", "thirdparty/sdl3webgpu.lua")

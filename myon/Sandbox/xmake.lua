target("MyonSandbox")
    if is_plat("macosx") then
      add_rules("xcode.application")
      add_files("resources/Info.plist")
    end

    set_kind("binary")
    set_languages("cxx20")

    add_files("src/Application.cpp")

    add_deps("MyonCore")


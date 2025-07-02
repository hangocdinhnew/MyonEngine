target("MyonSandbox")
    set_kind("binary")
    set_languages("cxx20")

    add_files("src/Application.cpp")

    add_deps("MyonCore")

    if is_plat("linux") then
      add_rpathdirs("$ORIGIN/../lib", {installonly = true})
    end

    if is_plat("macosx") then
      add_rpathdirs("@executable_path/../lib", {installonly = true})
    end

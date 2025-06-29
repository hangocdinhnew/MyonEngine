target("MyonSandbox")
    set_kind("binary")
    set_languages("cxx20")

    add_files("src/Application.cpp")

    add_deps("MyonCore")


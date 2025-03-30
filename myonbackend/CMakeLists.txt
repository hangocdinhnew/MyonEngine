# Set some stuff and do stuff
project(MyonBackend LANGUAGES CXX C)

set(MyonBackend_SOURCES
    "src/MyonBackend/Core/Log.cpp" "src/MyonBackend/Core/Engine.cpp"
    "src/MyonBackend/Core/Window.cpp")

# Make the library
add_library(MyonBackend STATIC "${MyonBackend_SOURCES}")
target_include_directories(MyonBackend PUBLIC "include/")

# Link libraries
target_link_libraries(MyonBackend PUBLIC spdlog::spdlog)
target_link_libraries(MyonBackend PUBLIC glfw)

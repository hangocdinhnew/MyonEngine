project(MyonSandbox LANGUAGES CXX C)

set(MyonSandbox_SOURCES "src/Application.cpp")

add_executable(MyonSandbox "${MyonSandbox_SOURCES}")
target_link_libraries(MyonSandbox PRIVATE MyonCore)

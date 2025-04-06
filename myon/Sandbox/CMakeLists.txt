project(MyonSandbox LANGUAGES CXX C)

set(MyonSandbox_SOURCES "src/Application.cpp")
set(MyonSandbox_SHADER_INPUT "${PROJECT_ROOT}/Shaders")
set(MyonSandbox_SHADER_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/Shaders")

add_custom_target(copy_shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${MyonSandbox_SHADER_INPUT} ${MyonSandbox_SHADER_OUTPUT}
    COMMENT "Copying directory/folder"
)

add_executable(MyonSandbox "${MyonSandbox_SOURCES}")
target_link_libraries(MyonSandbox PRIVATE MyonCore)

add_dependencies(MyonSandbox copy_shaders)

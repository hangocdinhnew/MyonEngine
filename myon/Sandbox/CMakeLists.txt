project(MyonSandbox LANGUAGES CXX C)

set(MyonSandbox_SOURCES "src/Application.cpp")
set(MyonSandbox_SHADER_INPUT "${PROJECT_ROOT}/Shaders")

add_executable(MyonSandbox "${MyonSandbox_SOURCES}")
target_link_libraries(MyonSandbox PRIVATE MyonCore)

install(TARGETS MyonSandbox
  RUNTIME DESTINATION bin
)
install(IMPORTED_RUNTIME_ARTIFACTS MyonSandbox)

install(DIRECTORY "${MyonSandbox_SHADER_INPUT}" DESTINATION bin/assets)

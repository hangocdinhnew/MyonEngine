project(MyonSandbox LANGUAGES CXX C)

set(MyonSandbox_SOURCES "src/Application.cpp")
set(MyonSandbox_SHADER_INPUT "${PROJECT_ROOT}/Shaders")

add_executable(MyonSandbox "${MyonSandbox_SOURCES}")
target_link_libraries(MyonSandbox PRIVATE MyonCore)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  set(SANITIZE_FLAGS "-fsanitize=address" "-fno-omit-frame-pointer")

  target_compile_options(MyonSandbox PRIVATE ${SANITIZE_FLAGS})
  target_link_options(MyonSandbox PRIVATE ${SANITIZE_FLAGS})
endif()

if (NOT WIN32)
set_target_properties(MyonSandbox PROPERTIES
  INSTALL_RPATH "/usr/local/lib;$ORIGIN/../lib;@executable_path/../lib"
)
endif()

install(IMPORTED_RUNTIME_ARTIFACTS MyonSandbox)

if (NOT WIN32)
install(TARGETS MyonSandbox
  RUNTIME DESTINATION bin
)
else()
install(TARGETS MyonSandbox
  RUNTIME DESTINATION .
)
endif()

if (NOT WIN32)
install(DIRECTORY "${MyonSandbox_SHADER_INPUT}" DESTINATION share/myonsandbox/assets)
else()
install(DIRECTORY "${MyonSandbox_SHADER_INPUT}" DESTINATION assets)
endif()

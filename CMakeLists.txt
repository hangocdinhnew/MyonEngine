cmake_minimum_required(VERSION 3.12)

# Set default build type early (before checking it!)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      "Debug"
      CACHE STRING "Sets build type" FORCE)
endif()

# Set optimization and debug flags based on build type
if(CMAKE_BUILD_TYPE MATCHES "Dist")
  set(CMAKE_CXX_FLAGS "-O3")
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
  set(CMAKE_CXX_FLAGS "-O3")
  add_compile_definitions(ENABLE_TRACING)
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
  set(CMAKE_CXX_FLAGS "-g")
endif()

if(WIN32 AND NOT MSVC)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

# Add variables
set(PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}")

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export compile commands for tools like clangd
option(CMAKE_EXPORT_COMPILE_COMMANDS "Exports compile_commands.json" ON)

# Maybe unused variables? (Not sure what this does, so leaving it)
option(MAYBE_UNUSED_VARIABLES "Maybe unused variables?" ON)

# Project definition
project(
  Myon
  LANGUAGES CXX C
  VERSION 0.1)

# Thirdparties
message(STATUS "Myon (Root): Preparing thirdparty dependencies...")
set(WEBGPU_BACKEND "WGPU")
set(WEBGPU_LINK_TYPE "STATIC")
add_subdirectory("${PROJECT_ROOT}/thirdparty/WebGPU")

option(SDL_STATIC "Make SDL a static library" ON)
option(SDL_SHARED "Make SDL a shared library" OFF)
add_subdirectory("${PROJECT_ROOT}/thirdparty/glm")
add_subdirectory("${PROJECT_ROOT}/thirdparty/spdlog")
add_subdirectory("${PROJECT_ROOT}/thirdparty/SDL")
add_subdirectory("${PROJECT_ROOT}/thirdparty/sdl3webgpu")

if(CMAKE_BUILD_TYPE MATCHES "Debug")
option(MYON_LOGTOFILE "Enables the log to file feature." OFF)
else()
option(MYON_LOGTOFILE "Enables the log to file feature." OFF)
endif()

message(
  STATUS "Myon (ROOT): Preparing Core, Core Extensions and the Applications...")
add_subdirectory("myon/Core")
add_subdirectory("myon/Sandbox")

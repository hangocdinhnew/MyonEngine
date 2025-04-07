cmake_minimum_required(VERSION 3.12)

# Set default build type early (before checking it!)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      "Debug"
      CACHE STRING "Sets build type" FORCE)
endif()

# Detect compiler
if(MSVC)
  message(FATAL_ERROR "Please do not use MSVC for this project!")
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
find_package(spdlog REQUIRED)
find_package(glslang REQUIRED)
find_package(SPIRV-Tools REQUIRED)
find_package(Vulkan REQUIRED COMPONENTS shaderc_combined)

option(SDL_STATIC "Make SDL a static library" ON)
option(SDL_SHARED "Make SDL a shared library" OFF)
find_package(SDL3 REQUIRED)

message(
  STATUS "Myon (ROOT): Preparing Core, Core Extensions and the Applications...")
add_subdirectory("myon/Core")
add_subdirectory("myon/Sandbox")

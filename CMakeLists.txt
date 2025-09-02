cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(MyonSandbox LANGUAGES CXX)

add_executable(MyonSandbox
  MyonSandbox/src/Application.cpp
)

add_subdirectory(MyonCore)

target_link_libraries(MyonSandbox PRIVATE myonruntime)

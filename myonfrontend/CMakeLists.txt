project(MyonFrontend LANGUAGES CXX C)

set(MyonFrontend_SOURCES "src/Application.cpp")

add_executable(MyonFrontend "${MyonFrontend_SOURCES}")
target_link_libraries(MyonFrontend PRIVATE MyonBackend)

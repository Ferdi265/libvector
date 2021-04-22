cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(libvector C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(libvector INTERFACE)
target_include_directories(libvector INTERFACE libvector/)

file(GLOB test-sources test/*.c)
add_executable(test ${test-sources})
target_link_libraries(test PRIVATE libvector)

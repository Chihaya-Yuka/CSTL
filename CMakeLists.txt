cmake_minimum_required(VERSION 3.5)

project(CSTL_example)

include_directories(src)

add_subdirectory(src)

add_executable(example example.c)

target_link_libraries(example CSTL)



cmake_minimum_required(VERSION 3.18)

project(funwithmemory)

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Boost REQUIRED COMPONENTS program_options)

add_subdirectory(src)


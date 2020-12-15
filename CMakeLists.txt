cmake_minimum_required(VERSION 3.4.1)

project(risc_vm)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include_directories(${PROJECT_SOURCE_DIR})
aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)

add_executable(riscvm ${SRCS})

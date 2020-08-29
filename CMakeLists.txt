cmake_minimum_required(VERSION 3.17.3)
project(common_template_base)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE TESTS RELATIVE ${CMAKE_SOURCE_DIR} "tests/*")

add_executable(common_template_base main.cpp shape_interface_example.h template_base_container.h template_base_interface_impl.h)
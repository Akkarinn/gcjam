cmake_minimum_required(VERSION 3.7)

project("google-code-jam" CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
 
add_subdirectory(${CMAKE_SOURCE_DIR}/gcj17)

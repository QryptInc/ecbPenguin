# Copyright © 2020, Qrypt, Inc., All rights reserved.

# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

project(penguinify_project VERSION 1.0.0)

enable_testing()

# Pull in requirements
find_package(OpenSSL MODULE REQUIRED)

set(EXE_NAME penguinify)
add_executable(${EXE_NAME} "")

target_sources(${EXE_NAME} PRIVATE
    src/penguinify.cpp
    src/ecbencryptor.cpp
    src/evpwrapper.cpp
    src/bitmapreader.cpp
    src/filewriter.cpp
    src/onetimepad.cpp
    src/qrngprocessor.cpp)

target_include_directories(${EXE_NAME} PRIVATE 
    ${OpenSSL_INCLUDE_DIRS}
    include )

target_link_libraries(${EXE_NAME} PRIVATE
    OpenSSL::OpenSSL)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    add_subdirectory(tests)
endif()

include(cmake/clang-cxx-dev-tools.cmake)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/Tux.bmp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/quantum.qrand
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
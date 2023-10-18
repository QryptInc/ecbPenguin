# Copyright © 2020, Qrypt, Inc., All rights reserved.

# Pull in requirements
find_package(GTest MODULE REQUIRED)
find_package(OpenSSL MODULE REQUIRED)

# Test target - we will add sources below
set(TEST_PROJECT "${EXE_NAME}_Test")
add_executable(${TEST_PROJECT} "")

configure_file(data/Tux.bmp ${CMAKE_CURRENT_BINARY_DIR}/Tux.bmp COPYONLY)

target_sources(${TEST_PROJECT} PRIVATE
    src/test_ecbencryptor.cpp
    ../src/ecbencryptor.cpp
    src/test_bitmapreader.cpp
    ../src/bitmapreader.cpp
    src/test_filewriter.cpp 
    ../src/filewriter.cpp
    src/test_evpwrapper.cpp
    ../src/evpwrapper.cpp)

target_include_directories(${TEST_PROJECT} PRIVATE 
    ${GTest_INCLUDE_DIRS}
    ${OpenSSL_INCLUDE_DIRS}
    include
    ../include)

target_link_libraries(${TEST_PROJECT} PRIVATE 
    GTest::GTest 
    OpenSSL::OpenSSL
    )

# Now let's define our test run
add_test(NAME unit COMMAND penguinify_Test)

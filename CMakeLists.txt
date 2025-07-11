cmake_minimum_required(VERSION 4.0.2)
project(GCLIB VERSION 0.1)

set(LIB "wecl")

set(CMAKE_C_STANDARD ${CMAKE_C_STANDARD_LATEST})
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/run")

add_library(${LIB} STATIC)
add_subdirectory(src)
target_include_directories(${LIB} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")


option(TEST_MODE "Enable or disable compiling the tests in tests folder (INSTEAD of library)" OFF)
if(TEST_MODE) # Compile test directory
    set(TEST "wecl_tests")
    add_executable(${TEST})
    add_subdirectory(tests)

    target_include_directories(${TEST} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
    target_link_libraries(${TEST} ${LIB})
endif()

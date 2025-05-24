cmake_minimum_required(VERSION 4.0.2)
project(GCLIB VERSION 0.1)

set(TARGET "gc")

set(CMAKE_C_STANDARD ${CMAKE_C_STANDARD_LATEST})
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/run")


option(TEST_MODE "Enable or disable compiling the tests in tests folder (INSTEAD of library)" ON)
if(TEST_MODE) # Compile test directory
    # add_executable(tests)
else() # Compile to lib

endif()

add_library(${TARGET} STATIC)
add_subdirectory(src)
target_include_directories(${TARGET} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")


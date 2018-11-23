cmake_minimum_required(VERSION 3.9)

project(rllib)
set(RLLIB_VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
if(NOT RLLIB_BUILD_EXAMPLES)
    set(RLLIB_BUILD_EXAMPLES False)
endif()
if(NOT RLLIB_BUILD_DOC)
    set(RLLIB_BUILD_DOC False)
endif()

set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Select the build type" FORCE)
set(RLLIB_BUILD_EXAMPLES ${RLLIB_BUILD_EXAMPLES} CACHE BOOL "Whether to build the examples" FORCE)
set(RLLIB_BUILD_DOC ${RLLIB_BUILD_DOC} CACHE BOOL "Whether to generate the documentation" FORCE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(src/rllib)
if(RLLIB_BUILD_EXAMPLES)
    add_subdirectory(examples/demo)
endif()
if(RLLIB_BUILD_DOC)
    add_subdirectory(doc)
endif()

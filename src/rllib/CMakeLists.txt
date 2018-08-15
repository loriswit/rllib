set(RLLIB_SRC_DIR ${PROJECT_SOURCE_DIR}/src/rllib)

if (NOT EXISTS ${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
    find_program(CONAN_PROGRAM conan)
    if (NOT CONAN_PROGRAM)
        message(FATAL_ERROR "Could not find program Conan")
    endif ()

    set(CONAN_SETTINGS build_type=${CMAKE_BUILD_TYPE})
    execute_process(COMMAND conan install ${RLLIB_SRC_DIR}
            --settings ${CONAN_SETTINGS}
            --install-folder ${PROJECT_BINARY_DIR}
            --build=missing)
endif ()

include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS)

file(GLOB_RECURSE RLLIB_SRC_FILES ${RLLIB_SRC_DIR}/*)

add_library(rl ${RLLIB_SRC_FILES})
target_include_directories(rl PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(rl z)

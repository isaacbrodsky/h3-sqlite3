# Copyright 2022 Isaac Brodsky
#
# Parts adapted from H3 CMakeLists.txt,
# Copyright 2022 Uber Technologies, Inc.
# Used under the Apache 2.0 license.

cmake_minimum_required(VERSION 3.20)

project(h3-sqlite3 LANGUAGES C)

set(H3EXT_VERSION 4.0.0)

set(LIB_SOURCE_FILES src/h3ext.c src/h3ext.h)
set(OTHER_SOURCE_FILES "")

include(CMakeDependentOption)

set(ALL_SOURCE_FILES
    ${LIB_SOURCE_FILES} ${OTHER_SOURCE_FILES})

add_library(h3ext ${LIB_SOURCE_FILES})

set_property(TARGET h3ext PROPERTY POSITION_INDEPENDENT_CODE ON)
if(NOT WIN32)
    # Compiler options are set only on non-Windows, since these options
    # are not correct for MSVC.
    target_compile_options(h3ext PRIVATE -Wall)

    target_compile_options(h3ext PRIVATE $<$<CONFIG:Debug>:-gdwarf-2 -g3 -O0 -fno-inline -fno-eliminate-unused-debug-types>)

    option(WARNINGS_AS_ERRORS "Warnings are treated as errors" OFF)
    if(WARNINGS_AS_ERRORS)
        target_compile_options(h3ext PRIVATE -Werror)
    endif()
endif()

find_library(H3_LIB h3)
target_link_libraries(h3ext PUBLIC h3)

# Automatic code formatting
# Give preference to clang-format-9
find_program(CLANG_FORMAT_PATH NAMES clang-format-9 clang-format)
cmake_dependent_option(
    ENABLE_FORMAT "Enable running clang-format before compiling" ON
    "CLANG_FORMAT_PATH" OFF)
if(ENABLE_FORMAT)
    # Format
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_PATH}
        -style=file
        -i
        ${ALL_SOURCE_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Formatting sources"
        )
    # Always do formatting
    add_dependencies(h3ext format)
elseif(NOT CLANG_FORMAT_PATH)
    message(WARNING "clang-format was not detected, "
                    "so automatic source code reformatting is disabled")
endif()

option(ENABLE_LINTING "Run clang-tidy on source files" ON)
find_program(CLANG_TIDY_PATH "clang-tidy")
cmake_dependent_option(
    ENABLE_LINTING "Enable running clang-tidy on sources during compilation" ON
    "CLANG_TIDY_PATH" OFF)
if(ENABLE_LINTING)
    set_target_properties(h3ext PROPERTIES C_CLANG_TIDY "${CLANG_TIDY_PATH}")
elseif(NOT CLANG_TIDY_PATH)
    message(WARNING "clang-tidy was not detected, "
                  "so source code linting is disabled")
endif()

# Docs
find_package(Doxygen)
option(ENABLE_DOCS "Enable building documentation." ON)
if(DOXYGEN_FOUND AND ENABLE_DOCS)
    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_CURRENT_BINARY_DIR}/dev-docs/_build")
    configure_file(dev-docs/Doxyfile.in
        dev-docs/Doxyfile
        ESCAPE_QUOTES
        )
    add_custom_target(docs
        ALL
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/dev-docs/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dev-docs
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
else()
    add_custom_target(docs
        echo "Doxygen was not installed when CMake was run or ENABLE_DOCS was OFF. Check that Doxygen is installed and rerun `cmake .`" VERBATIM
        )
endif()

# TODO: Testing
# TODO: Installation

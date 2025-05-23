# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MUST be SHARED library, static don't compile with project
add_library(jsi SHARED
        jsi.cpp)

include_directories(../include)

target_include_directories(jsi PUBLIC ..)

## Enable bitcode
#set(HERMES_ENABLE_BITCODE OFF CACHE BOOL
#        "Include bitcode with the framework")

set(jsi_compile_flags "")
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" OR
    "${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
  list(APPEND jsi_compile_flags "-Wno-non-virtual-dtor")
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
  # Turn on Error Handling in MSVC, otherwise objects are not destructed
  # when they go out of scope due to exceptions.
  list(APPEND jsi_compile_flags "/EHsc")
endif()
if (HERMES_ENABLE_BITCODE)
  list(APPEND jsi_compile_flags "-fembed-bitcode")
endif ()
target_compile_options(jsi PRIVATE ${jsi_compile_flags})

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/jsi/" DESTINATION include
  FILES_MATCHING PATTERN "*.h"
  PATTERN "test" EXCLUDE)

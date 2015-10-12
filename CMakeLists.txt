cmake_minimum_required (VERSION 2.6)
project (Sandwiches)
set (Sandwiches_VERSION_MAJOR 0)
set (Sandwiches_VERSION_MINOR 1)

include(FindPkgConfig)
enable_testing()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_C_FLAGS "-O1 -Wall -std=gnu11")

configure_file (
  "${PROJECT_SOURCE_DIR}/src/sandwiches_config.h.in"
  "${PROJECT_BINARY_DIR}/sandwiches_config.h"
  )


pkg_search_module(GLib REQUIRED glib-2.0)
include_directories(${GLib_INCLUDE_DIRS})
set(LIBS ${LIBS} ${GLib_LIBRARIES})

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/tests")

add_subdirectory(src)
add_subdirectory(tests)


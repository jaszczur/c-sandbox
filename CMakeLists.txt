cmake_minimum_required (VERSION 2.6)
project (Sandwiches)
set (Sandwiches_VERSION_MAJOR 0)
set (Sandwiches_VERSION_MINOR 1)

include(FindPkgConfig)
enable_testing()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
configure_file (
  "${PROJECT_SOURCE_DIR}/src/sandwiches_config.h.in"
  "${PROJECT_BINARY_DIR}/sandwiches_config.h"
  )


pkg_search_module(Eina REQUIRED eina)
include_directories(${Eina_INCLUDE_DIRS})
set(LIBS ${LIBS} ${Eina_LIBRARIES})

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/tests")

add_subdirectory(src)
add_subdirectory(tests)


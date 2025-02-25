cmake_minimum_required(VERSION 3.31)

if(NOT DEFINED PICO_SDK_PATH)
  set(PICO_SDK_PATH "$ENV{PICO_SDK_PATH}" CACHE PATH "Path to PICO SDK")  
endif()

project(
  raspiccolo
  VERSION 0.0.1
  DESCRIPTION ""
  LANGUAGES C CXX ASM)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

include(PropertyUtils)
include(DocsUtils)

#add_compile_options(-Wall -Wextra -pedantic -Werror)

set(raspiccolo_BUILD_DOCS
    ON
    CACHE BOOL "Whether or not to build documentation.")
  set(raspiccolo_BUILD_TESTS
    ON
    CACHE BOOL "Whether or not to build tests.")

set(MODULE_ROOT "${PROJECT_SOURCE_DIR}/include")

add_subdirectory(raspiccolo)


if(raspiccolo_BUILD_TESTS)
  # enable_testing() 
  # add_subdirectory(tests)
endif()

if(raspiccolo_BUILD_DOCS)
  add_subdirectory(docs)
endif()

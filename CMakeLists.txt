cmake_minimum_required(VERSION 3.31)

if(NOT DEFINED PICO_SDK_PATH)
  #message(FATAL_ERROR "PICO_SDK_PATH is not defined!")
  #TODO: Set chache variable and then if still not defined we can throw error
  set(PICO_SDK_PATH "$ENV{PICO_SDK_PATH}" CACHE PATH "Path to PICO SDK")  
endif()

# For now / maybe make an option
set(PICO_DEOPTIMIZED_DEBUG ON)

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake RESULT_VARIABLE resVar)

message(STATUS ${resVar})

project(
  raspiccolo
  VERSION 0.0.1
  DESCRIPTION ""
  LANGUAGES C CXX ASM)

pico_sdk_init()


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

include(PropertyUtils)
include(DocsUtils)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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

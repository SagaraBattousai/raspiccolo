cmake_minimum_required(VERSION 3.31)

# Custom setup, There isnt a default for libraries so lets try and make one.
# We still need to copy pico_sdk_import.cmake incase it is being built as a
# standalone library.

# I have thought of some interesting/cleaver ways of doing this but I think that
# Raspberry Pi have already considered all of this, I just want to be careful 
# not to override anything a parent project may have set.

# if PICO_SDK_PATH is neither a cache or normal variable (we wont check whether 
# PICO_SDK_PATH is an environment variable as the next stage does this) then
# it is unlikly this library has been included as a subproject.
if(NOT DEFINED PICO_SDK_PATH)
# Enable users to set PICO_SDK_PATH as a cache value to override
set(CACHE{PICO_SDK_PATH} TYPE PATH)

# If PICO_SDK_PATH is not defined then 
#  message(FATAL_ERROR "PICO_SDK_PATH is not defined!")
#  #TODO: Set chache variable and then if still not defined we can throw error
#  set(PICO_SDK_PATH "$ENV{PICO_SDK_PATH}" CACHE PATH "Path to PICO SDK")  
#endif()

#include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake RESULT_VARIABLE resVar)



project(
  raspiccolo
  VERSION 0.0.1
  DESCRIPTION ""
  LANGUAGES C CXX ASM)

# pico_sdk_init()


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

include(PropertyUtils)
include(DocsUtils)
include(StandardSetupUtils)

set_language_standards(C 11 CXX 20)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#add_compile_options(-Wall -Wextra -pedantic -Werror)

set(raspiccolo_BUILD_DOCS
    ON
    CACHE BOOL "Whether or not to build documentation.")
  set(raspiccolo_BUILD_TESTS
    ON
    CACHE BOOL "Whether or not to build tests.")

set(MODULE_ROOT "${PROJECT_SOURCE_DIR}/include")

# add_subdirectory(raspiccolo)


if(raspiccolo_BUILD_TESTS)
  # enable_testing() 
  # add_subdirectory(tests)
endif()

if(raspiccolo_BUILD_DOCS)
  add_subdirectory(docs)
endif()

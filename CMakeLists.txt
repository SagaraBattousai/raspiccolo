# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 4.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake")

include(CmakeUtils)


set_language_standards(C 11 CXX 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Very similar setup to the Raspberry Pi Pico VS Code Extension boilerplate but
# with cache variables as this is a library and therefore should be more
# flexible. For example users may want to build without the VS Code extension
# (since the debugging capabilities etc are not entirly neccisary without an
# actual application (plus I'm a fan of visual studios but too lazy (right now)
# to develop a plugin to do it for me)).
if(WIN32)
  set(USERHOME $ENV{USERPROFILE})
else()
  set(USERHOME $ENV{HOME})
endif()

set(CACHE{sdkVersion} TYPE STRING HELP "Pico SDK version string" VALUE 2.2.0)
set(CACHE{toolchainVersion} TYPE STRING HELP "Toolchain version string" VALUE
                            14_2_Rel1)
set(CACHE{picotoolVersion} TYPE STRING HELP "Picotool version string" VALUE
                           2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if(EXISTS ${picoVscode})
  include(${picoVscode})
endif()

set_cache_choices(
  PICO_BOARD
  VALUE
  pico
  CHOICES
  pico
  pico_w
  pico2
  pico2_w)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(
  raspiccolo
  VERSION 0.0.1
  DESCRIPTION ""
  LANGUAGES C CXX ASM)

pico_sdk_init()

include(PropertyUtils)
include(DocsUtils)

option(PICO_DEOPTIMIZED_DEBUG ON)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# add_compile_options(-Wall -Wextra -pedantic -Werror)

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

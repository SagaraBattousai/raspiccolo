cmake_minimum_required(VERSION 3.29)

project(
  <Project_Name>
  VERSION <x.y.z>
  DESCRIPTION ""
  LANGUAGES C CXX)

# Leave C++ standard up to the root application, so set it only if this is the
# current top-level CMake project.
if(CMAKE_SOURCE_DIR STREQUAL <Project_Name>_SOURCE_DIR)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_C_STANDARD 11)
  set(CMAKE_C_STANDARD_REQUIRED ON)
else()
  if(CMAKE_CXX_STANDARD LESS 20)
    message(
      FATAL_ERROR
        "thoth requires CMAKE_CXX_STANDARD >= 20 (got: ${CMAKE_CXX_STANDARD})")
  endif()
  if(CMAKE_C_STANDARD LESS 11)
    message(
      FATAL_ERROR
        "thoth requires CMAKE_C_STANDARD >= 11 (got: ${CMAKE_C_STANDARD})")
  endif()
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

include(SystemCheck)
include(LibUtils)
include(PropertyUtils)
include(DocsUtils)

set_system_check_vars()

if(MSVC)
  # Wall removed as msvc has some errors that trigger this
  add_compile_options(/permissive- /WX /W4) # Wall)
  # set(VS_STARTUP_PROJECT "")
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(<Project_Name>_BUILD_DOCS
    ON
    CACHE BOOL "Whether or not to build documentation.")
  set(<Project_Name>_BUILD_TESTS
    ON
    CACHE BOOL "Whether or not to build tests.")


set(MODULE_ROOT "${PROJECT_SOURCE_DIR}/include")

add_subdirectory(<Project_Name>)


if(<Project_Name>_BUILD_TESTS)
  # enable_testing() 
  # add_subdirectory(tests)
endif()

if(<Project_Name>_BUILD_DOCS)
  add_subdirectory(docs)
endif()

# if(MSVC) 
  # set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT <Startup_Project>)
# endif()

# ----------------------------------------------
# Install settings
# ----------------------------------------------

# include(GNUInstallDirs)

# set(IN_BUILD_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}")

# set(INSTALL_IN_BUILD OFF CACHE BOOL "If set, the CMAKE_INSTALL_PREFIX will be
# set to the build directory\ (unless CMAKE_INSTALL_PREFIX has been set by the
# user).\nIn this case\ CMAKE_INSTALL_PREFIX = ${IN_BUILD_INSTALL_PREFIX}")

# if(INSTALL_IN_BUILD AND NOT CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
# set(CMAKE_INSTALL_PREFIX "${IN_BUILD_INSTALL_PREFIX}" CACHE PATH "..." FORCE)
# endif()

# install(TARGETS <Target_Name> RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION
# ${CMAKE_INSTALL_LIBDIR})

# install(TARGETS cactuar FILE_SET public_headers DESTINATION
# ${CMAKE_INSTALL_INCLUDEDIR}) install(IMPORTED_RUNTIME_ARTIFACTS
# OpenSSL::Crypto RUNTIME_DEPENDENCY_SET external_runtime_deps RUNTIME)

# if(BUILD_DOCS) #Use trailing slashes to avoid adding subdirectories
# install(DIRECTORY "${CMAKE_SOURCE_DIR}/docs/build/sphinx/" DESTINATION
# ${CMAKE_INSTALL_DOCDIR})

# install(DIRECTORY "${CMAKE_SOURCE_DIR}/docs/build/man/" DESTINATION
# ${CMAKE_INSTALL_MANDIR}) endif()

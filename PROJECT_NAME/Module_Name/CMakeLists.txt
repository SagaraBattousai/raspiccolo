
set(<Module_Name>_MODULE_ROOT "${MODULE_ROOT}/<Project_Name>/<Module_Name>")

set(cpp_sources "")
set(c_sources "")
set(<Module_Name>_module
  #"${<Module_Name>_MODULE_ROOT}/xyz.h"
  )

add_library(<Module_Name> SHARED ${cpp_sources} ${c_sources})

target_sources(<Module_Name> PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${<Module_Name>_module}
  "${MODULE_ROOT}/_<Project_Name>_config.h"
  )

if (MSVC)
  target_compile_definitions(<Module_Name> PRIVATE <Module_Name>_BUILD_DLL)
endif()

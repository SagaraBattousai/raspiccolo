
set(PWM_MODULE_ROOT "${MODULE_ROOT}/raspiccolo/pwm")

#set(cpp_sources "")
set(c_sources "")
set(pwm_module
  #"${<Module_Name>_MODULE_ROOT}/xyz.h"
  )

add_library(pwm INTERFACE ${c_sources}) # ${cpp_sources})

target_sources(pwm PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${pwm_module}
  # "${MODULE_ROOT}/_<Project_Name>_config.h"
  )

target_compile_definitions(pwm INTERFACE c_std_11)

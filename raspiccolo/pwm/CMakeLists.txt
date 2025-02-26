
set(PWM_MODULE_ROOT "${MODULE_ROOT}/raspiccolo/pwm")

#set(cpp_sources "")
set(c_sources "pwm.c")
set(pwm_module
  "${PWM_MODULE_ROOT}/pwm.h"
  )

#add_library(raspiccolo_pwm INTERFACE ${c_sources}) # ${cpp_sources})
# OKAY!!! Im going to switch to a static or (probably more likely) object library
# I wanted to do INTERFACE library like PICO_SDK but ... I can't link pico's header ...
# Because target_link_library requires INTERFACE (could normal link_library work?)
add_library(raspiccolo_pwm STATIC ${c_sources}) # ${cpp_sources})

target_sources(raspiccolo_pwm PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${pwm_module}
  # "${MODULE_ROOT}/_<Project_Name>_config.h"
  )

#target_link_libraries(raspiccolo_pwm INTERFACE hardware_pwm hardware_clocks)
target_link_libraries(raspiccolo_pwm PUBLIC hardware_pwm hardware_clocks hardware_gpio)

# target_compile_definitions(raspiccolo_pwm INTERFACE c_std_11)

add_library(raspiccolo::pwm ALIAS raspiccolo_pwm)


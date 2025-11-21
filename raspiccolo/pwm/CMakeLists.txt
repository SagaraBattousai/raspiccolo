
set(PWM_MODULE_ROOT "${MODULE_ROOT}/raspiccolo/pwm")

set(cpp_sources "pwm.cpp")
set(c_sources "pwm.c")
set(pwm_module
  "${PWM_MODULE_ROOT}/pwm.h"
  )

add_library(raspiccolo_pwm STATIC ${c_sources} ${cpp_sources})

target_sources(raspiccolo_pwm PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${pwm_module}
  )

target_link_libraries(raspiccolo_pwm PUBLIC hardware_pwm hardware_clocks hardware_gpio)

target_compile_definitions(raspiccolo_pwm PUBLIC c_std_11)

add_library(raspiccolo::pwm ALIAS raspiccolo_pwm)


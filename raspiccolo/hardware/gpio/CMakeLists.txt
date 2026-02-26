
set(GPIO_MODULE_ROOT "${MODULE_ROOT}/raspiccolo/gpio")

#set(cpp_sources "")
set(c_sources "gpio.c")
set(gpio_module
  "${GPIO_MODULE_ROOT}/gpio.h"
  )

add_library(raspiccolo_gpio STATIC ${c_sources}) # ${cpp_sources})

target_sources(raspiccolo_gpio PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${gpio_module}
  )

target_link_libraries(raspiccolo_gpio PRIVATE hardware_gpio)

target_compile_definitions(raspiccolo_gpio PRIVATE c_std_11)

add_library(raspiccolo::gpio ALIAS raspiccolo_gpio)


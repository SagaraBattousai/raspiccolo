
set(I2C_MODULE_ROOT "${MODULE_ROOT}/raspiccolo/i2c")

#set(cpp_sources "")
set(c_sources "i2c.c")
set(i2c_module
  "${I2C_MODULE_ROOT}/i2c.h"
  )

add_library(raspiccolo_i2c STATIC ${c_sources}) # ${cpp_sources})

target_sources(raspiccolo_i2c PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${i2c_module}
  )

target_link_libraries(raspiccolo_i2c PRIVATE hardware_i2c hardware_gpio)

target_compile_definitions(raspiccolo_i2c PRIVATE c_std_11)

add_library(raspiccolo::i2c ALIAS raspiccolo_i2c)


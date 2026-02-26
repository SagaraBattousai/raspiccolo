// SPDX-License-Identifier: Apache-2.0
// Copyright © 2025-2026 James Calo


#include <raspiccolo/i2c/i2c.h>

#include <hardware/gpio.h>
#include <hardware/i2c.h>

#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5
#define I2C_BAUD_RATE 400000 // 400Khz


int f() {
// I2C Initialisation. Using it at 400Khz.
i2c_init(I2C_PORT, I2C_BAUD_RATE);
    
gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
gpio_pull_up(I2C_SDA);
gpio_pull_up(I2C_SCL);


    return 0;
}

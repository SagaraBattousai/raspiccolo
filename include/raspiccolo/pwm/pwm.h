#ifndef __RASPICCOLO_PWM_H__
#define __RASPICCOLO_PWM_H__

#include <stdint.h>

#include <hardware/pwm.h>
#include <hardware/gpio.h>

typedef struct pwm_pin {
    unsigned pin;
    unsigned slice_num; //worth carrying around? or better to just get each time?
    unsigned chan; //worth carrying around? or better to just get each time? Could just use pin % 2....
    uint16_t wrap;
    //unsigned freq;
    //uint16_t duty;
} pwm_pin_t;

//TODO: Need a way to determine if underlying pwm slice is already in use.
//For now, just be careful as I think is the case anyway.

//Okay, I still don't 100% get static inline vs inline as msvc seems to treat them the same but from what I get
// Static stops issues with Multiple definitions but apparently inline does too so.....
static inline void setup_pwm_pin(unsigned pin, pwm_pin_t *pwm_pin) {
    pwm_pin->pin = pin;
    gpio_set_function(pin, GPIO_FUNC_PWM);
    pwm_pin->slice_num = pwm_gpio_to_slice_num(pwm_pin->pin);
    pwm_pin->chan = pwm_gpio_to_channel(pwm_pin->pin);
    pwm_pin->wrap = 0;
}

void set_pwm_freq(unsigned freq, pwm_pin_t *pwm_pin);

void set_pwm_duty(float duty, pwm_pin_t *pwm_pin);

void set_pwm_duty_u16(uint16_t duty, pwm_pin_t *pwm_pin);

static inline void enable_pwm(pwm_pin_t *pwm_pin) {
    pwm_set_enabled(pwm_pin->slice_num, true);
}

static inline void disable_pwm(pwm_pin_t *pwm_pin) {
    pwm_set_enabled(pwm_pin->slice_num, false);
}

#endif
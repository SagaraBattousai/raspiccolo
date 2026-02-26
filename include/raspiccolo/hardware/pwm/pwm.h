// SPDX-License-Identifier: Apache-2.0
// Copyright © 2025-2026 James Calo

#ifndef __RASPICCOLO_PWM_H__
#define __RASPICCOLO_PWM_H__

#include <hardware/gpio.h>
#include <hardware/pwm.h>

#ifdef __cplusplus
extern "C" {
#endif

// uint is typedefed to unsigned int in pico/types.h included by pico.h included
// by both hardware imports above!

typedef struct pwm_pin {
  uint pin;
  uint slice_num;
  uint chan;  //Could just use pin % 2....
  uint16_t wrap;
  //uint freq;
  //uint16_t duty;
} pwm_pin_t;


// TODO: Need a way to determine if underlying pwm slice is already in use.
// For now, just be careful as I think is the case anyway.

// Okay, I still don't 100% get static inline vs inline vs extern inline (I mean
// I do understand it but it's finiky). By leaving it static inline we get
// safety if its not inlined (as would be an issue with just inline) without the
// downside of unreachable code (as would be the issue with extern inline if
// every call was inlined) but with possible duplication if more than one
// translation unit does not inline the function (an alternative would be a .c
// with the extern declaration packaged into a static library so the linker
// would only use it if it were not inlined)
static inline void setup_pwm_pin(uint pin, pwm_pin_t* pwm_pin) {
  pwm_pin->pin = pin;
  gpio_set_function(pin, GPIO_FUNC_PWM);
  pwm_pin->slice_num = pwm_gpio_to_slice_num(pwm_pin->pin);
  pwm_pin->chan = pwm_gpio_to_channel(pwm_pin->pin);
  pwm_pin->wrap = 0;
  //pwm_pin->freq = 0;
  //pwm_pin->duty=0;
}

void set_pwm_freq(uint freq, pwm_pin_t* pwm_pin);

void set_pwm_duty(float duty, pwm_pin_t* pwm_pin);

void set_pwm_duty_u16(uint16_t duty, pwm_pin_t* pwm_pin);

static inline void enable_pwm(pwm_pin_t* pwm_pin, bool enable) {
  pwm_set_enabled(pwm_pin->slice_num, enable);
}

#ifdef __cplusplus
namespace raspiccolo {

// Just a nicer interface, nothing actually done, maybe good or maybe dumb?
class PwmPin {
 public:
static PwmPin Setup(uint pin) { return PwmPin(pin, false); }
static PwmPin SetupAndEnable(uint pin) { return PwmPin(pin, true); }

void Freq(uint freq) {
    set_pwm_freq(freq, &_pin);
}

void Duty(float duty) {
    Duty((uint16_t)(duty * _pin.wrap));
}

void Duty(uint16_t duty) {
    set_pwm_duty_u16(duty, &_pin);
}

void Enable(bool enable) {
  enable_pwm(&_pin, enable);
}

 private:
 PwmPin(uint pin, bool enable=false) {
    setup_pwm_pin(pin, &_pin);
    enable_pwm(&_pin, enable);
 }

 pwm_pin_t _pin;

};
}  // namespace raspiccolo
#endif

#ifdef __cplusplus
}
#endif

#endif

#include <pico/float.h>
#include <hardware/pwm.h>
#include <hardware/clocks.h>

#include <raspiccolo/pwm/pwm.h>

static const float CLOCK_DIVIDER = 4096.f;

void set_pwm_freq(uint freq, pwm_pin_t *pwm_pin) {
    // Set clock divisor to allow maximum level/duty (i.e. increasing resolution)
    uint32_t base_clk = clock_get_hz(clk_sys);
    uint32_t divider_16ths = float2uint(
        ceilf(base_clk / (CLOCK_DIVIDER * freq))
    ); 
    //Don't need _z as always +ve so -inf is fine
    // ^^ is it faster though?
    
    float div_clk = base_clk / (divider_16ths / 16.f);
    
    uint8_t div_frac = divider_16ths & 0x0F; // 16ths_remainder
    uint8_t div_int = divider_16ths >> 4; 

    pwm_set_clkdiv_int_frac(pwm_pin->slice_num, div_int, div_frac);

    //Warning to myself, dangerous to set to struct first as not "officially" set yet.
    pwm_pin->wrap = ((uint16_t)(div_clk / freq)) - 1;
    pwm_set_wrap(pwm_pin->slice_num, pwm_pin->wrap);
}

//Pre cond: 0 <= cond <= 1.0f
void set_pwm_duty(float duty, pwm_pin_t *pwm_pin) {
    set_pwm_duty_u16((uint16_t)(duty * pwm_pin->wrap), pwm_pin);
}

//Pre cond: 0 <= duty <= wrap
void set_pwm_duty_u16(uint16_t duty, pwm_pin_t *pwm_pin) {
    pwm_set_chan_level(pwm_pin->slice_num, pwm_pin->chan, duty);
}
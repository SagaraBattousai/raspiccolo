#include <math.h>

#include <hardware/pwm.h>
#include <hardware/clocks.h>

#include <raspiccolo/pwm/pwm.h>

//As values are required to be in 16'ths
//#define HEX_SCALE 16 //think of a better name
#define MAX_BYTES 65536 //think of a better name
#define CLOCK_DIVIDER 4096.0f

//pwm_set_clkdiv_int_frac(slice_num, 38, 3);

//pwm_set_wrap(slice_num, 65465);

//pwm_set_chan_level(slice_num, chan, 65465/2);

//pwm_set_enabled(slice_num, true);

//gpio_set_function(PWM_GPIO, GPIO_FUNC_PWM);
//uint slice_num = pwm_gpio_to_slice_num(PWM_GPIO);
//uint chan = pwm_gpio_to_channel(PWM_GPIO);

void set_pwm_freq(unsigned freq, pwm_pin_t *pwm_pin) {
    // Set clock divisor to allow maximum level/duty (i.e. increasing resolution)
    uint32_t base_clk = clock_get_hz(clk_sys);
    unsigned divider = (unsigned) ceil(base_clk / (CLOCK_DIVIDER * freq));
    
    float new_clk = base_clk / (divider / 16.0f);
    
    uint8_t div_frac = divider & 0x0F;
    uint8_t div_int = divider >> 4;

    pwm_set_clkdiv_int_frac(pwm_pin->slice_num, div_int, div_frac);

    //Warning to myself, dangerous to set to struct first as not "officially" set yet.
    pwm_pin->wrap = (uint16_t)((new_clk / freq) - 1);
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
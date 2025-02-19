#include "driver/ledc.h"

#define PWM_FREQ        5000        // PWM Frequency in Hz
#define PWM_RESOLUTION  LEDC_TIMER_8_BIT  // 8-bit resolution (0-255)
#define PWM_TIMER       LEDC_TIMER_0
#define PWM_CHANNEL     LEDC_CHANNEL_0

#define DUTY_CYCLE_MAX 200
#define DUTY_CYCLE_MIN 0
#define DUTY_CYCLE_STEP 10
#define DUTY_CYCLE_RANGE (DUTY_CYCLE_MAX - DUTY_CYCLE_MIN)


class AnalogLed
{
private:
    gpio_num_t pin;
    int is_going_up = 1; // 1 if the brightness is increasing, 0 if decreasing
    TickType_t interval_per_step; 
    TickType_t last_update_time = 0; 
    ledc_channel_config_t ledc_channel = {}; //config for LED
    ledc_timer_config_t ledc_timer = {};  //config for LED
public:
    void init(gpio_num_t pin);
    void update();
    void setLed(int value);
    void sin(int period);
};


#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

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
    bool is_going_up = true;  // 1 if the brightness is increasing, 0 if decreasing
    bool run_once = false;
    bool is_running = false;  // When false, the LED is in constant brightness mode
    TickType_t interval_per_step; 
    TickType_t last_update_time = 0; 
    ledc_channel_config_t ledc_channel = {}; // Config for LED
    ledc_timer_config_t ledc_timer = {};  // Config for LED
    
public:
    void init(gpio_num_t pin);
    void update();
    void setLed(int value);  // Set LED to a specific brightness instantly
    void sin(int period);    // Set the LED to a sinusoidal pattern
};

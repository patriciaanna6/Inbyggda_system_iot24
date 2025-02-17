#include "driver/ledc.h"

#define PWM_FREQ        5000 //PWM Frequency in Hz
#define PWM_RESOLUTION  LEDC_TIMER_8_BIT //8-bit resolution (0-255)
#define PWM_TIMER       LEDC_TIMER_0
#define PWM_CHANNEL     LEDC_CHANNEL_0  
#define DUTY_CYCLE_MAX 200
#define DUTY_CYCLE_MIN 0
#define DUTY_CYCLE_RANGE (DUTY_CYCLE_MAX - DUTY_CYCLE_MIN)
#define DUTY_STEP  5 //Step size for brightness adjustment

class AnalogLed
{
    private:
    gpio_num_t pin;
    ledc_channel_config_t ledc_channel = {};
    ledc_timer_config_t ledc_timer = {};
    int current_duty = DUTY_CYCLE_MIN;
    bool increasing = true;


    public: 
    void init(gpio_num_t pin); //input
    void update();
    void setLed(int value);
    void sin(int period);


};


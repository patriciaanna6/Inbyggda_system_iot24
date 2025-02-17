#include "driver/ledc.h"

#define PWM_FREQ        5000 //PWM Frequency in Hz
#define PWM_RESOLUTION  LEDC_TIMER_8_BIT //8-bit resolution (0-255)
#define PWM_TIMER       LEDC_TIMER_0
#define PWM_CHANNEL     LEDC_CHANNEL_0  

class AnalogLed
{
    private:
    gpio_num_t pin;
    ledc_channel_config_t ledc_channel = {};
    ledc_timer_config_t ledc_timer = {};

    public: 
    void init(gpio_num_t pin); //input
    //void update
    void setLed(int value);
    void sin(int period);


};


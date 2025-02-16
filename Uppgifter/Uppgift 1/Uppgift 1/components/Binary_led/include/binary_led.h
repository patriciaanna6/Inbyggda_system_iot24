#include "driver/gpio.h"

class BinaryLed
{
    private:
    gpio_num_t pin; 
    
    public:
    void init(gpio_num_t pin_input); //input
    //void update
    void setLed(bool led_state); //Set GPIO level to input value
    void blink(int milliseconds_on, int milliseconds_off);
};

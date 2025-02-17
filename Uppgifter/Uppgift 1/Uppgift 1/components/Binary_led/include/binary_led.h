#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"

class BinaryLed
{
    private:
    gpio_num_t pin; 
    int blink_on_time = 500; //Default 500 ms
    int blink_off_time = 500; //Default 500ms
    bool led_state = false; 
    TickType_t last_toggle_time = 0;
    
    public:
    void init(gpio_num_t pin_input); //input
    void update();
    void setLed(bool led_state); //Set GPIO level to input value
    void blink(int milliseconds_on, int milliseconds_off);
};

#ifndef BINARY_LED_H
#define BINARY_LED_H

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class BinaryLed {
private:
    gpio_num_t pin;
    bool led_state;
    TickType_t last_toggle_time;
    int blink_on_time = 500;  // 500ms
    int blink_off_time = 500;
    bool is_blinking = true; // starts to blink
public:
    void init(gpio_num_t pin_input);
    void update();
    void setLed(bool led_state);
    void blink(int milliseconds_on, int milliseconds_off);
};

#endif // BINARY_LED_H

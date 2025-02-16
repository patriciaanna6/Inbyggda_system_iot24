#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "binary_led.h"

static const char *TAG = "example"; //for printing 

void BinaryLed::init(gpio_num_t pin_input)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");

    this->pin = pin_input;

    gpio_reset_pin(pin); //Reset the GPIO to its default state
    gpio_set_direction(pin, GPIO_MODE_OUTPUT); //Set the GPIO as a output
    }

    //void update - ingen aning

    void BinaryLed::setLed(bool led_state)
    {
        gpio_set_level(this->pin, led_state);
    }
    void BinaryLed::blink(int milliseconds_on, int milliseconds_off)
    {
        gpio_set_level(this->pin, 1); //Lights on
        vTaskDelay(milliseconds_on / portTICK_PERIOD_MS); //delay
        gpio_set_level(this->pin, 0); //Lights off 
        vTaskDelay(milliseconds_off / portTICK_PERIOD_MS);
    }



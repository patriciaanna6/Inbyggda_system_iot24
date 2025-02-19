#include "Button.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/mpu_wrappers.h"
#include "esp_log.h"

extern "C" {
}

Button::Button(gpio_num_t pin) : pin(pin), buttonReleased(false), startTickButton(0) {} //Saving the input arguments to private variabel

// Initialization method to configure ESP-IDF GPIO settings
void Button::init() {
    gpio_config_t buttonConfi;g
        buttonConfig.mode = GPIO_MODE_INPUT; //Set as input
        buttonConfig.intr_type = GPIO_INTR_DISABLE; // No delays
        buttonConfig.pin_bit_mask = (1ULL << pin); // Choose the pin
        buttonConfig.pull_up_en = GPIO_PULLUP_DISABLE;
        buttonConfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
    esp_err_t error = gpio_config(&buttonConfig);

    if (error != ESP_OK) {
        printf("GPIO configuration failed for pin %d with error code: %d\n", pin, error);
    }
}

void Button::update (){
    int gpio_level = gpio_get_level(this->pin); //Read GPIO level

    if(gpio_level == 1 && !this->buttonReleased){ // If there is power, GPIO level = 1

        this->buttonReleased = true; // Button not pressed
        this->startTickButton = xTaskGetTickCount();

        if(this->onPressedCallback){ // Checks that the callback is set
            this->onPressedCallback(this->pin);
        }
    }
    else if(gpio_level == 0 && this->buttonReleased){ // If there is no power, GPIO level = 0
        TickType_t timeSincePressed = xTaskGetTickCount() - startTickButton;
        if(timeSincePressed >= pdMS_TO_TICKS(10)){

            this->buttonReleased = false; //Button is pressed
            this->startTickButton = xTaskGetTickCount();
       } 
    }

}
// Checks if the button is pressed
bool Button::is_pressed() {
    return !this->buttonReleased;
}

void Button::setOnPressed(void(*callback)(int pin)){
    this->onPressedCallback = callback;
}





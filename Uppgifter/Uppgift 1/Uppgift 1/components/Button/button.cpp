#include "Button.h"
#include <stdio.h>



Button::Button(gpio_num_t pin, bool active_high) : pin(pin), active_high(active_high) {}

// Initieringsmetod för att konfigurera ESP-IDF GPIO-inställningar
void Button::init() {
    gpio_config_t buttonConfig;
    buttonConfig.mode = GPIO_MODE_INPUT;              // Ställ in som ingång
    buttonConfig.intr_type = GPIO_INTR_DISABLE;       // Inga avbrott
    buttonConfig.pin_bit_mask = (1ULL << pin);        // Välj rätt pin

    // Ställ in pull-up eller pull-down baserat på aktiv hög/låg
    if (active_high){
        buttonConfig.pull_up_en = GPIO_PULLUP_ENABLE;
    }else {
        buttonConfig.pull_up_en = GPIO_PULLUP_DISABLE;
    }
    if (active_high){
        buttonConfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
    }else{
        buttonConfig.pull_down_en = GPIO_PULLDOWN_ENABLE;
    }
    esp_err_t error = gpio_config(&buttonConfig);

    if (error != ESP_OK) {
        printf("GPIO configuration failed for pin %d with error code: %d\n", pin, error);
    }
}

void Button::update (){
    gpio_num_t gpio_pin_number = (gpio_num_t)this->pin;
    int gpio_level = gpio_get_level(gpio_pin_number);

    if(gpio_level == 1 && this->buttonReleased == false){

        this->buttonReleased = true;
        this->startTickButton = xTaskGetTickCount();

        this->onPressed(this->pin);
    }
    if(gpio_level == 0 && buttonReleased == true){
        TickType_t timesSincePressed = xTaskGetTickCount() - startTickButton;
        if(timeSincePressed >= pdMS_TO_TICKS(10)){
            this->onReleased(this->pin);

            this->buttonReleased = false;
            this->startTickButton = xTaskGetTickCount();
        }
    }

}

// Kontrollera om knappen är tryckt
bool Button::is_pressed() {
    int level = gpio_get_level(pin);
    return active_high ? (level == 1) : (level == 0);
}






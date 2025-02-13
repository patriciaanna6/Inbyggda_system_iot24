#include "Button.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/mpu_wrappers.h"

extern "C" {

}

Button::Button(gpio_num_t pin, bool active_high) : pin(pin), active_high(active_high), buttonReleased(false), startTickButton(0) {}

// Initieringsmetod för att konfigurera ESP-IDF GPIO-inställningar
void Button::init() {
    gpio_config_t buttonConfig;
        buttonConfig.mode = GPIO_MODE_INPUT; // Ställ in som ingång
        buttonConfig.intr_type = GPIO_INTR_DISABLE; // Inga avbrott
        buttonConfig.pin_bit_mask = (1ULL << pin); // Välj rätt pin
        buttonConfig.pull_up_en = GPIO_PULLUP_DISABLE;
        buttonConfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
    esp_err_t error = gpio_config(&buttonConfig);

    if (error != ESP_OK) {
        printf("GPIO configuration failed for pin %d with error code: %d\n", pin, error);
    }
}

void Button::update (){
    int gpio_level = gpio_get_level(this->pin); //Läs ut GRPIO-nivån

    if(gpio_level == 1 && !this->buttonReleased){ //Om det finns ström gpio level = 1

        this->buttonReleased = true; //Knappen ej tryck
        this->startTickButton = xTaskGetTickCount();
    }
    else if(gpio_level == 0 && this->buttonReleased){ //Om det inte finns ström gpio level = 0
        TickType_t timeSincePressed = xTaskGetTickCount() - startTickButton;
        if(timeSincePressed >= pdMS_TO_TICKS(10)){
            printf("Knappen är nedtryckt!\n");
            
            //this->onReleased(this->pin);

            this->buttonReleased = false; //Knappen tryck
            this->startTickButton = xTaskGetTickCount();
        }
    }


}
// Kontrollera om knappen är tryckt
bool Button::is_pressed() {
    return !this->released;

}







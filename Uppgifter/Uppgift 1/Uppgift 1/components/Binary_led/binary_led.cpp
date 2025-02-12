#include <stdio.h>
#include "binary_led.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"


#define LED_PIN GPIO_NUM_2 


void init(int pin){
    gpio_set_direction((gpio_num_t)pin, GPIO_MODE_OUTPUT);
    
}

void update(){
    //void;
}

void setLed(int pin, int state){

}

void blink(int ms_on, int ms_off){
    //gpio_set_level(BLINK_GPIO, s_led_state); 

}

/*void app_main() {
    init(LED_PIN);  // Initiera LED på definierad pin
    
    while (1) {
        gpio_set_level(LED_PIN, 1);  // Tänd LED
        vTaskDelay(pdMS_TO_TICKS(1000));  // Vänta 1 sekund
        
        gpio_set_level(LED_PIN, 0);  // Släck LED
        vTaskDelay(pdMS_TO_TICKS(1000));  // Vänta 1 sekund
    }
}*/


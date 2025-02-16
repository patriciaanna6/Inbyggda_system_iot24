#include <stdio.h>
#include "binary_led.h"
#include "button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void buttonPressedCallback(int pin){
    printf("Hello Philippines\n");
}

extern "C" void app_main(void){
    Button myButton(GPIO_NUM_3);
    myButton.init();
    myButton.setOnPressed(buttonPressedCallback);

    while (1){
        myButton.update();
        vTaskDelay(pdMS_TO_TICKS(10));
    }


//init(3);
//update();
//setLed(3000, 3000);
//blink(5000,5000);

}
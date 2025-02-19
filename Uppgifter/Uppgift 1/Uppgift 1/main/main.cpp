#include <stdio.h>
#include "binary_led.h"
#include "button.h"
#include "analog_led.h"
#include "potentiometer.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "esp_adc_cal.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define CONFIG_BLINK_PERIOD 250
#define BLINK_GPIO (gpio_num_t)4
#define SIN_GPIO (gpio_num_t)15
#define POTENTIOMETER_GPIO (adc1_channel_t)ADC1_CHANNEL_6

static const char *TAG = "example"; //for printing only

//Callback for button
void buttonPressedCallback(int pin){
    printf("Hello Philippines\n");
}
void thresholdCrossedCallback(int pin_adc, int value){
    ESP_LOGI(TAG, "Callback: threshold crossed in pin %d value %d\n", pin_adc, value);
}

extern "C" void app_main(void){
    //Test for button
    Button myButton(GPIO_NUM_3);
    myButton.init();
    myButton.setOnPressed(buttonPressedCallback);

    /*Test BinaryLed
    ESP_LOGI(TAG, "Init BinaryLed");
    BinaryLed led_B;
    led_B.init(BLINK_GPIO);
    led_B.blink(1000, 1000); // Blink 1 second on, 1 second off*/

    /*Test AnalogLed
    ESP_LOGI(TAG, "Init AnalogLed");
    AnalogLed led_A;
    led_A.init(SIN_GPIO);
    led_A.sin(4000); // Sin wave with 4 seconds period (2 seconds up, 2 seconds down)*/

    /*Test Potentiometer
    ESP_LOGI(TAG, "Init Potentiometer");
    Potentiometer pot;
    pot.init(POTENTIOMETER_GPIO);
    pot.setOnThreshold(2000, true, thresholdCrossedCallback);*/

    while(1) {
        myButton.update();
        //led_B.update(); //binary_led
        //led_A.update(); //analog_led
        //pot.update(); //potentiometer
        vTaskDelay(pdMS_TO_TICKS(100));
    }

//init(3);
//update();
//setLed(3000, 3000);
//blink(5000,5000);

}
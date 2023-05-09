/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"


#define PIN 2

void app_main(void)
{
    gpio_pad_select_gpio(PIN); // Escolher pino
    gpio_set_direction(PIN, GPIO_MODE_OUTPUT); // Mode do pino
    bool status = 0;

    while(1){
        status = !status;
        gpio_set_level(PIN,status);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay. porTick é tempo d maquina em milisegundos.
    }
}

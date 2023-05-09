#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"


#define PIN 13

// Um milisegundo é pouco pra ESP, ele não tem tempo de fazer tudo nesse tempo, então da erro.
// O ets_delay funciona pq usa outro núcleo.Núcleos diferentes tempos diferentes.

void app_main(void)
{
    gpio_pad_select_gpio(PIN);
    gpio_set_direction(PIN, GPIO_MODE_OUTPUT);

    bool status = 0;

    while(1){
        
        gpio_set_level(PIN,0);
        gpio_set_level(PIN,1);
        ets_delay_us(1000);
        gpio_set_level(PIN,0);
        ets_delay_us(1000);
        vTaskDelay(10 / portTICK_PERIOD_MS); // porTICK é de calibração de milisegundos. Pode ser necessário ajustar.               
    }
}
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/dac.h"

/*
Contrário do ADC. Dá um valor em binário, ele anda pra um correspondente.
*/
void app_main(void)
{
    dac_output_enable(DAC_CHANNEL_1);
 
    //int volt = 3.3;
    //int PCM = (int)((float)(255*volt)/3.3);
    while(1){
        for (int i = 0; i< 255; i++){
            dac_output_voltage(DAC_CHANNEL_1,i); // Funçã já faz uma senoide.
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
    }
    
}
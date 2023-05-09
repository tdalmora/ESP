/* 
Conversão de um sinal analógico para digital:
    Em resumo, pegar um valor analógico (5.75V, por exemplo), 
    e colocá-lo em um range de 0 a 1023, por exemplo. Por que de 0 a 1023?
    Por que é binário, ou seja (00000000 até 11111111).
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "driver/adc.h"


void app_main(void)
{
   adc1_config_width(ADC_WIDTH_BIT_12); //Define resolução.
   adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11); // Aplica ganho?

   adc2_config_channel_atten(ADC2_CHANNEL_0, ADC_ATTEN_DB_11);
   while (true)
   {
       int val1 = 0;
       int val2 = 0;
       val1 = adc1_get_raw(ADC1_CHANNEL_4); // --> Pegar o valor no instante discretizado.
       adc2_get_raw(ADC2_CHANNEL_0,ADC_WIDTH_BIT_12, &val2); //--> Retorna o erro e coloca na val2.
       
       printf("ADC1: %fV ADC2: %fV \n", val1*(3.3/4095), val2*(3.3/4095));       
       vTaskDelay(100 / portTICK_PERIOD_MS);
   }
   
}


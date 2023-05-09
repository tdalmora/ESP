#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/ledc.h"

void pwm_init(void){ //Função que inicializa as configuraç~ies do pwm.
    ledc_timer_config_t ledc_timer = { //Config do timer 
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num  = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_13_BIT,
        .freq_hz  = 5000,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = { //Config do canal
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = 25,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&ledc_channel);
}

void app_main(void)
{
   pwm_init();
   for (int duty = 0; duty < 8192; duty++){
        ledc_set_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0, duty); //2^13 =  8192, setando o valor do duty.
        ledc_update_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0); // Atualizando la na config o valor.
        vTaskDelay(10 / portTICK_PERIOD_MS);
   }

}
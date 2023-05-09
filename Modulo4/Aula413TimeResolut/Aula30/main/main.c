#include <stdio.h>
#include "esp_timer.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void disparoTimer1(void *arg){
    static bool status;
    status = !status;
    gpio_set_level(GPIO_NUM_25,status);
}

void app_main(void)
{
    gpio_pad_select_gpio(GPIO_NUM_25);
    gpio_set_direction(GPIO_NUM_25, GPIO_MODE_OUTPUT);
    
    const esp_timer_create_args_t timer1Conf = {
        .callback = disparoTimer1,
        .name = "Timer1"
    };

    esp_timer_handle_t timer1Handle;
    esp_timer_create(&timer1Conf,&timer1Handle);
    esp_timer_start_periodic(timer1Handle,50);
    
    for(int i=0; i<5; i++){
        esp_timer_dump(stdout);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    esp_timer_stop(timer1Handle);
    esp_timer_delete(timer1Handle);
}
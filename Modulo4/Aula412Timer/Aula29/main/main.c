#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_system.h"

void disparo(TimerHandle_t xTimer){
    printf("Disparado em %lld \n", esp_timer_get_time()/1000);
}

void app_main(void)
{
  printf("Sistema iniciado em %lld \n", esp_timer_get_time()/1000);
  TimerHandle_t xTimer = xTimerCreate("timer disparo",pdMS_TO_TICKS(500),true,NULL,disparo);
  xTimerStart(xTimer,0);
}
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void Task1(void * params){
    while(1){
        printf("Realizando leitura de temperatura %s \n", (char *) params);
        vTaskDelay (1000 / portTICK_PERIOD_MS);
    }
}

void Task2(void * params){
    while(1){
        printf("Realizando leitura de umidade %s\n",(char *) params);
        vTaskDelay (2000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    xTaskCreate(&Task1,"Leitura de temperatura",2048,"Task 1",5,NULL);
    xTaskCreatePinnedToCore(&Task2,"Leitura de umidade"    ,2048,"Task 2",2,NULL,1);
}
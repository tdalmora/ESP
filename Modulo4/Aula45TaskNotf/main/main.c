#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static TaskHandle_t tasksHandler = NULL;
int DATA[5] = {0};

void Task1(void * params){
    while(1){
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        xTaskNotify(tasksHandler,0b00001,eSetBits);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        xTaskNotify(tasksHandler,0b00010,eSetBits);
        vTaskDelay(1000 / portTICK_PERIOD_MS);  
        xTaskNotify(tasksHandler,0b00100,eSetBits);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        xTaskNotify(tasksHandler,0b01000,eSetBits);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        xTaskNotify(tasksHandler,0b10000,eSetBits);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
   }
}

void Task2(void * params){
    uint estado = 0;
    while(1){
        xTaskNotifyWait(estado,0,&estado,portMAX_DELAY);
        printf("Notificação recebida %d \n", estado);
    }
}

void app_main(void)
{
    xTaskCreate(&Task1,"Task1",2048,NULL,2,&tasksHandler);
    xTaskCreate(&Task2,"Task2",2048,NULL,2,&tasksHandler);
}
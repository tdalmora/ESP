#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xSemaphoreHandle semaforo;

void comTask(void * params){
    while(1){    
        printf("Recebido dado \n");
        xSemaphoreGive(semaforo);
        printf("Novo processamento\n");
        vTaskDelay (5000 / portTICK_PERIOD_MS);
    }
}

void procTask(void * params){
    while(1){        
        xSemaphoreTake(semaforo, portMAX_DELAY);
        printf("Iniciando Processamento \n");
    }
}

void app_main(void)
{    
    semaforo = xSemaphoreCreateBinary();
    xTaskCreate(&comTask,"Task de comuniocação",2048,NULL,2,NULL);
    xTaskCreate(&procTask,"Task de execução"    ,2048,NULL,1,NULL);
}
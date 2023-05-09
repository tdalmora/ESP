#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xQueueHandle queue;

void comTask(void * params){
    int counter = 0;
    while(1){    
        counter++;
        printf("Recebido dado \n");
        long result = xQueueSend(queue, &counter, 1000 / portTICK_PERIOD_MS);
        if (result){
            printf("Dado inserido na fila com sucesso \n");
        }else{
            printf("Erro ao inserir dado na fila \n");
        }

        vTaskDelay (5000 / portTICK_PERIOD_MS);
    }
}

void procTask(void * params){
    while(1){        
        int receive = 0;
        long result = xQueueReceive(queue, &receive, 2000 / portTICK_PERIOD_MS);
        if (result){
            printf("Iniciando Processamento - Dado recebido: %d \n", receive);
        }        
    }
}

void app_main(void)
{    
    queue = xQueueCreate(4,sizeof(int));
    xTaskCreate(&comTask,"Task de comuniocação",2048,NULL,2,NULL);
    xTaskCreate(&procTask,"Task de execução"   ,2048,NULL,1,NULL);
}
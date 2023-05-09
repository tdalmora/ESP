#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

EventGroupHandle_t grupoEvt;
const int goCom = BIT0;    //0b01
const int goSensor = BIT1; //0b10


void comTask(void * params){    
    while(1){            
        printf("Recebido dado \n");
        xEventGroupSetBits(grupoEvt, goCom);
        vTaskDelay (1000 / portTICK_PERIOD_MS);
    }
}

void sensorTask(void * params){
    while(1){            
        printf("Realizado leitura\n");
        xEventGroupSetBits(grupoEvt, goSensor);
        vTaskDelay (5000 / portTICK_PERIOD_MS);
    }
}

void procTask(void * params){
    while(1){        
        xEventGroupWaitBits(grupoEvt,goCom | goSensor, true, true, portMAX_DELAY);
        printf("Recebido requisição e leitura do sensor \n");
    }
}

void app_main(void)
{    
    grupoEvt = xEventGroupCreate();
    xTaskCreate(&comTask,"Task de comunicação",2048,NULL,1,NULL);
    xTaskCreate(&sensorTask,"Task de sensor"  ,2048,NULL,1,NULL);
    xTaskCreate(&procTask,"Task de execução"  ,2048,NULL,1,NULL);
}
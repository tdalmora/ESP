#include <stdio.h>
#include "esp_log.h" // Trazem LOG --> Ferramenta pra debugar e enviar infos pelo UART.

void app_main(void)
{
    // Ordem de prioridade. A tag é pra identificar de quem que é este log.
    int var = 0;
    ESP_LOGE("LOG1","LOG DE ERRO %d", var++);                  //Erro
    ESP_LOGW("LOG1","LOG DE WARNING/AVISO %d", var++);         //Warning
    ESP_LOGI("LOG1","LOG DE INFORMAÃ‡ÃƒO %d", var++);          //Info
    ESP_LOGD("LOG1","LOG DE DEBUG %d", var++);                 //Debug
    ESP_LOGV("LOG1","LOG DE TEXTO COMUM/VERBOSE %d", var++);   //Informações gerais

    esp_log_level_set("LOG2",ESP_LOG_DEBUG); // Habilita o nível de log pra tag LOG2.
    ESP_LOGE("LOG2","LOG DE ERRO");
    ESP_LOGW("LOG2","LOG DE WARNING/AVISO");
    ESP_LOGI("LOG2","LOG DE INFORMAÃ‡ÃƒO");
    ESP_LOGD("LOG2","LOG DE DEBUG");
    ESP_LOGV("LOG2","LOG DE TEXTO COMUM/VERBOSE");
}
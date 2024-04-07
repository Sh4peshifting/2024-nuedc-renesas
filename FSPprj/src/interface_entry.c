#include "interface.h"
#include "user.h"
/* interface entry function */
/* pvParameters contains TaskHandle_t */
void interface_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);
    /* TODO: add your own code here */
    esp_init();

    while (1)
    {
        status_upload();
        
        vTaskDelay(800);
    }
}

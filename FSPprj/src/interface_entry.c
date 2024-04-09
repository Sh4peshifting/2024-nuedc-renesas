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
        // uprintf(&g_uart8_ctrl,"GET /index/\r\n");
        // xSemaphoreTake(uart8rxc,1000);
        // R_SCI_UART_Write(&g_uart7_ctrl,uart8pack.data,uart8pack.len);
        // xSemaphoreTake(uart7txc,portMAX_DELAY);
        vTaskDelay(700);

    }
}

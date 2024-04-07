#include "hmi.h"
#include "user.h"
/* hmi entry function */
/* pvParameters contains TaskHandle_t */
void hmi_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);

    /* TODO: add your own code here */
    while (1)
    {
        // if(xSemaphoreTake(uart9rxc,0) == pdTRUE){
        //     R_SCI_UART_Write(&g_uart7_ctrl,uart9pack.data,uart9pack.len);
        //     xSemaphoreTake(uart7txc,portMAX_DELAY);
        //     screen_rx_proc(uart9pack.data,uart9pack.len);
        // }

        xSemaphoreTake(uart9rxc,portMAX_DELAY);
        screen_rx_proc(uart9pack.data,uart9pack.len);
        vTaskDelay(2);
    }
}

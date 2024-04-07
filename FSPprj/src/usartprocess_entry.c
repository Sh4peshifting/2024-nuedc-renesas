#include "usartprocess.h"
#include "user.h"
/* usartprocess entry function */
/* pvParameters contains TaskHandle_t */
void usartprocess_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);
    /* TODO: add your own code here */
    R_SCI_UART_Open(&g_uart9_ctrl,&g_uart9_cfg);
    uint32_t nowtime;
    while (1)
    {
        nowtime = xTaskGetTickCount();
        if (nowtime - uart9pack.time >= 10){
            uart9pack.len = uart9pack.cnt;
            if (uart9pack.cnt) xSemaphoreGive(uart9rxc);
            uart9pack.cnt = 0;
        }
        if (nowtime - uart8pack.time >= 10){
            uart8pack.len = uart8pack.cnt;
            if (uart8pack.cnt) xSemaphoreGive(uart8rxc);
            uart8pack.cnt = 0;
        }
        if (nowtime - uart8pack.time >= 10){
            uart4pack.len = uart4pack.cnt;
            if (uart4pack.cnt) xSemaphoreGive(uart4rxc);
            uart4pack.cnt = 0;
        }
        if (nowtime - uart8pack.time >= 5){
            uart5pack.len = uart5pack.cnt;
            if (uart5pack.cnt) xSemaphoreGive(uart5rxc);
            uart5pack.cnt = 0;
        }

        vTaskDelay(2);
    }
}


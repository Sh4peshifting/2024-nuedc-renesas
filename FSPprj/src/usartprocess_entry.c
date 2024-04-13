#include "usartprocess.h"
#include "user.h"
/* usartprocess entry function */
/* pvParameters contains TaskHandle_t */
void usartprocess_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);
    /* TODO: add your own code here */
    g_uart7.p_api->open(g_uart7.p_ctrl, g_uart7.p_cfg);
    R_SCI_UART_Open(&g_uart9_ctrl,&g_uart9_cfg);
    R_SCI_UART_Open(&g_uart8_ctrl,&g_uart8_cfg);
    R_SCI_UART_Open(&g_uart4_ctrl,&g_uart4_cfg);
    R_SCI_UART_Open(&g_uart5_ctrl,&g_uart5_cfg);
    uint32_t nowtime;
    while (1)
    {
        nowtime = xTaskGetTickCount();
        if (nowtime - uart9pack.time >= 10){
            if (uart9pack.cnt) {
                uart9pack.len = uart9pack.cnt;
                uart9pack.cnt = 0;
                xSemaphoreGive(uart9rxc);            
            }
        }
        if (nowtime - uart8pack.time >= 10){
            if (uart8pack.cnt){
                uart8pack.len = uart8pack.cnt;
                uart8pack.cnt = 0;
                xSemaphoreGive(uart8rxc);
            }
            
        }
        if (nowtime - uart4pack.time >= 10){
            if (uart4pack.cnt){
                uart4pack.len = uart4pack.cnt;
                uart4pack.cnt = 0;
                if(0x65 == uart4pack.data[0] && 0x55 == uart4pack.data[1])
                xSemaphoreGive(uart4rxc);

            }
        }
        if (nowtime - uart5pack.time >= 5){
            if (uart5pack.cnt){
                uart5pack.len = uart5pack.cnt;
                uart5pack.cnt = 0;
                xSemaphoreGive(uart5rxc);
            }
        }

        vTaskDelay(2);
    }
}


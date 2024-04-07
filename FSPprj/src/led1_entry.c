#include "led1.h"
#include "user.h"

/* led1 entry function */
/* pvParameters contains TaskHandle_t */
void led1_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);
    /* TODO: add your own code here */
    g_uart7.p_api->open(g_uart7.p_ctrl,g_uart7.p_cfg);
    // R_SCI_UART_Open(&g_uart9_ctrl,&g_uart9_cfg);
    ws2812_Init();
    motor_init();
    motion_cfg(0,0.1f,0.1f);
//    DHT11_Data dht11;
//    DHT11_Data_TypeDef dht11_data;
    // motion_step(40000,1);
    motion_cfg(0.2f,0,0);
    while (1)
    {
        // dht11=read_dht11();
        // Read_DHT11(&dht11_data);
        // uprintf(&g_uart7_ctrl,"temp:%d.%d,humi:%d.%d\n",dht11_data.temp_int,dht11_data.temp_deci,
        // dht11_data.humi_int,dht11_data.humi_deci);

        // uprintf(&g_uart7_ctrl,"hello\n");
        // light_ctrl(LIGHT_ON);
        // R_IOPORT_PinWrite(g_ioport.p_ctrl, led, 0);
        // vTaskDelay(500);
        // // light_ctrl(LIGHT_OFF);
        // R_IOPORT_PinWrite(g_ioport.p_ctrl, led, 1);
        // vTaskDelay(500);
        // xSemaphoreTake(uart9rxc,portMAX_DELAY);
        // R_SCI_UART_Write(&g_uart7_ctrl,uart9pack.data,uart9pack.len);
        // xSemaphoreTake(uart7txc,portMAX_DELAY);
        vTaskDelay(1);

    }
}

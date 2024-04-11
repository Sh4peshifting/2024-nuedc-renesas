#include "led1.h"
#include "user.h"
#include <string.h>

/* led1 entry function */
/* pvParameters contains TaskHandle_t */
void led1_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);
    /* TODO: add your own code here */
    
    // R_SCI_UART_Open(&g_uart9_ctrl,&g_uart9_cfg);
    ws2812_Init();
    motor_init();
    ic_detect_init();
    // motion_cfg(0, 0.2f, 0);
    // vTaskDelay(3000);
    // motion_cfg(0.2f, 0, 0);
    // vTaskDelay(3000);
    //    DHT11_Data dht11;
    //    DHT11_Data_TypeDef dht11_data;
    // motion_step(40000, 1);
    // vTaskDelay(200);
    // motion_step(40000, 0);
    // motion_cfg(0.3f, 0.3f, 0);

    uint8_t card_id[5];
    uint8_t a=0;
    while (1)
    {
        // dht11=read_dht11();
        // Read_DHT11(&dht11_data);
        // uprintf(&g_uart7_ctrl,"temp:%d.%d,humi:%d.%d\n",dht11_data.temp_int,dht11_data.temp_deci,
        // dht11_data.humi_int,dht11_data.humi_deci);

        // uprintf(&g_uart7_ctrl,"hello\n");
        light_ctrl(LIGHT_ON);
        R_IOPORT_PinWrite(g_ioport.p_ctrl, led, 0);
        vTaskDelay(500);
        light_ctrl(LIGHT_OFF);
        R_IOPORT_PinWrite(g_ioport.p_ctrl, led, 1);
        vTaskDelay(500);
        // xSemaphoreTake(uart9rxc,portMAX_DELAY);
        // R_SCI_UART_Write(&g_uart7_ctrl,uart9pack.data,uart9pack.len);
        // xSemaphoreTake(uart7txc,portMAX_DELAY);

        // a=read_card(card_id, NULL);
        // uprintf(&g_uart7_ctrl, "card id:%02x%02x%02x%02x   %d\n", 
        //     card_id[0], card_id[1], card_id[2], card_id[3],a);
        // memset(card_id, 0, 5);
  

        vTaskDelay(1);
        
    }
}

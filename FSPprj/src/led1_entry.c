#include "led1.h"
#include "user.h"
#include <string.h>

/* led1 entry function */
/* pvParameters contains TaskHandle_t */
void led1_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);
    /* TODO: add your own code here */

    ws2812_Init();
    uint8_t ledcnt=0;
    while (1)
    {
        if(light_status==1){
            ws2812_Set_one_LED_Color(0,C_white);
            ws2812_Set_one_LED_Color(7,C_white);
            light_status=0;
        }
        else if(light_status==2){
            ws2812_Set_one_LED_Color(0,0);
            ws2812_Set_one_LED_Color(7,0);
            light_status=0;
        }

        if(0==onworking){
            ws2812_Set_one_LED_Color(1,0);
            ws2812_Set_one_LED_Color(2,0);
            ws2812_Set_one_LED_Color(3,0);
            ws2812_Set_one_LED_Color(4,0);
            ws2812_Set_one_LED_Color(5,0);
            ws2812_Set_one_LED_Color(6,0);
        }
        else{
            if(ledcnt){
                ws2812_Set_one_LED_Color(1,C_Blue);
                ws2812_Set_one_LED_Color(2,C_Blue);
                ws2812_Set_one_LED_Color(3,C_Blue);
                ws2812_Set_one_LED_Color(4,C_Red);
                ws2812_Set_one_LED_Color(5,C_Red);
                ws2812_Set_one_LED_Color(6,C_Red);
            }
            else{
                ws2812_Set_one_LED_Color(1,C_Red);
                ws2812_Set_one_LED_Color(2,C_Red);
                ws2812_Set_one_LED_Color(3,C_Red);
                ws2812_Set_one_LED_Color(4,C_Blue);
                ws2812_Set_one_LED_Color(5,C_Blue);
                ws2812_Set_one_LED_Color(6,C_Blue);
            }
            ledcnt=!ledcnt;
        }

        ws2812_Send_Data();
        R_IOPORT_PinWrite(g_ioport.p_ctrl, led, 0);
        vTaskDelay(300);
        R_IOPORT_PinWrite(g_ioport.p_ctrl, led, 1);
        vTaskDelay(300);
        
    }
}

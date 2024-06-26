#include "hal_data.h"
#include "stdio.h"
#include "semphr.h"
#include "user.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "fire_alarm.h"

uartpack uart9pack={{0},0,0,0};
uartpack uart8pack={{0},0,0,0};
volatile uartpack uart5pack={{0},0,0,0};
volatile uartpack uart4pack={{0},0,0,0};

uint32_t  step_position;
float speed_forward,target_angle;
volatile uint8_t onworking=0,run_mode;

uint8_t username[20],password[20];

void uart7_callback(uart_callback_args_t * p_args)
{
    switch (p_args->event)
    {
        BaseType_t rx;
        case UART_EVENT_TX_COMPLETE:
        {
            xSemaphoreGiveFromISR(uart7txc,&rx);
            break;
        }
        case UART_EVENT_RX_COMPLETE:
        {
            xSemaphoreGiveFromISR(uart7rxc,&rx);
            break;
        }
        default:
        {
            break;
        }
    }
    
}

void uart9_callback(uart_callback_args_t * p_args)
{
    switch (p_args->event)
    {
        BaseType_t rx;
        case UART_EVENT_RX_CHAR:
        {
            uart9pack.time= xTaskGetTickCount();
            // R_SCI_UART_Read(&g_uart9_ctrl,&uart9pack.data[uart9pack.cnt],1);
            uart9pack.data[uart9pack.cnt]=(uint8_t)(p_args->data);
            uart9pack.cnt++;
            break;
        }
        case UART_EVENT_TX_COMPLETE:
        {
            xSemaphoreGiveFromISR(uart9txc,&rx);
            break;
        }
        default:
        {
            break;
        }
    }
    
}

void uart8_callback(uart_callback_args_t * p_args)
{
    switch (p_args->event)
    {
        BaseType_t rx;
        case UART_EVENT_RX_CHAR:
        {
            uart8pack.time= xTaskGetTickCount();
            uart8pack.data[uart8pack.cnt]=(uint8_t)(p_args->data);
            uart8pack.cnt++;
            break;
        }
        case UART_EVENT_TX_COMPLETE:
        {
            xSemaphoreGiveFromISR(uart8txc,&rx);
            break;
        }
        default:
        {
            break;
        }
    }
    
}

void uart45_callback(uart_callback_args_t * p_args)
{
    switch (p_args->event)
    {
        case UART_EVENT_RX_CHAR:
        {
            if(p_args->channel==4){
                uart4pack.time= xTaskGetTickCount();
                uart4pack.data[uart4pack.cnt]=(uint8_t)(p_args->data);
                uart4pack.cnt++;
            }
            else if(p_args->channel==5){
                uart5pack.time= xTaskGetTickCount();
                uart5pack.data[uart5pack.cnt]=(uint8_t)(p_args->data);
                uart5pack.cnt++;
            }
            break;
        }
        case UART_EVENT_TX_COMPLETE:
        {

            break;
        }
        default:
        {
            break;
        }
    }
    
}
// int fputc(int ch, FILE *f)
// {
//     g_uart7.p_api->write(g_uart7.p_ctrl, (uint8_t const *const)&ch, 1);
//     xSemaphoreTake(uart7txc,portMAX_DELAY);

//     return ch;
// }

void uprintf(uart_ctrl_t *p_ctrl,char *fmt, ...)
{
    char buf[256];
    va_list ap;
    va_start(ap,fmt);
    vsprintf(buf,fmt,ap);
    va_end(ap);

    R_SCI_UART_Write(p_ctrl,(uint8_t *)buf,strlen(buf));
    
    if(p_ctrl==&g_uart7_ctrl) xSemaphoreTake(uart7txc,portMAX_DELAY);
    else if(p_ctrl==&g_uart8_ctrl) xSemaphoreTake(uart8txc,portMAX_DELAY);

}


uint8_t isonline()
{
    bsp_io_level_t level;
    R_IOPORT_PinRead(&g_ioport_ctrl,track2,&level);
    if(level==BSP_IO_LEVEL_HIGH) return 1;
    else return 0;
}

void turn_to(uint8_t dir)
{
    if(dir == TurnLeft) target_angle = read_yaw()+90.0f;
    else if(dir == TurnRight) target_angle = read_yaw()-90.0f;
    else if(dir == TurnBack){
        target_angle = read_yaw()-180.0f;
    }
    run_mode=RunAngle;
    vTaskDelay(2200);
    if(dir == TurnBack) vTaskDelay(600);
    run_mode=RunIdle;
}

void go_to_line1(float speed)
{
    speed_forward=speed;
    run_mode=RunForward;
    while(!isonline()){
        vTaskDelay(2);
    }
    while(isonline()){
        vTaskDelay(2);
    }
    run_mode=RunIdle;
    speed_forward=0;
    vTaskDelay(200);
    return;
}

void go_to_line(uint8_t line)
{
    speed_forward=0.3f;
    run_mode=RunForward;
    while(line){
        while(!isonline()){
            vTaskDelay(2);
        }
        line--;
        vTaskDelay(100);
    }
    run_mode=RunIdle;
    speed_forward=0;
    vTaskDelay(300);

}

void back_to_cross(uint8_t nn)
{
    speed_forward=-0.3f;
    run_mode=RunForward;//后退为负速度的前进

    while (nn--)
    {
        while (k210pack.data[SignIndex] != SignCross)
        {
            vTaskDelay(2);
        }
        vTaskDelay(1000);
    }

    run_mode=RunIdle;
    speed_forward=0;
    vTaskDelay(500);
    
}

void go_to_cross(uint8_t nn)
{
    speed_forward=0.25f;
    run_mode=RunForward;//后退为负速度的前进

    while (nn--)
    {
        while (k210pack.data[SignIndex] != SignCross)
        {
            vTaskDelay(2);
        }
        if(nn==0) break;
        vTaskDelay(1000);
    }

    run_mode=RunIdle;
    speed_forward=0;
    vTaskDelay(300);  
}

void slide_to_line(uint8_t dir,uint8_t nn)
{
    speed_forward=0.28f;
    if(dir== SlideLeft) target_angle = -90.0f;
    else if(dir== SlideRight) target_angle = 90.0f;
    run_mode=RunVt;

    while (nn--)
    {
        while (abs(128 - (int)(k210pack.data[3]))>50)
        {
            vTaskDelay(2);
        }
        if(nn==0) break;
        vTaskDelay(1800);
    }

    run_mode=RunIdle;
    speed_forward=0;
    vTaskDelay(300); 

}


void set_position(uint32_t pos)
{
    if(pos== step_position) return;
    uint8_t dir = pos > step_position ? 1 : 0;
    if(dir) motion_step(pos-step_position, 1);
    else motion_step(step_position-pos, 0);
    
    step_position = pos;

}

// void go_time(void)
// {
//     run_mode=RunForward;
//     speed_forward=0.3f;
//     vTaskDelay(2000);
//     run_mode=RunIdle;
//     speed_forward=0;
// }

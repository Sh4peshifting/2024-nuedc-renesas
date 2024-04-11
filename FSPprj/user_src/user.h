#ifndef __USER_H
#define __USER_H

#include "FreeRTOS.h"
#include "task.h"
#include "ws2812.h"
#include "dht11.h"
#include "motor.h"
#include "interface_driver.h"
#include "screen_uart.h"
#include "fire_alarm.h"
#include "ic_detect.h"

#define osDelay(milisec) vTaskDelay(milisec)

#define RunForward 0
#define RunBackward 1
#define RunAngle 2
#define RunIdle 3

#define WORK_IN 1
#define WORK_OUT 2
#define WORK_CH 3
#define WORK_IDLE 0


#define TurnLeft 0
#define TurnRight 1

// 0x00	直线模式
// 0x01	初始化成功
// 0x02	到达十字中心
// 0x03	达到终点
// 0x04	到达车库
// 0x05	未识别到红线

#define SignCross 0x02
#define SignIndex 2
#define k210pack uart4pack

typedef struct 
{
    uint8_t data[256];
    uint8_t len;
    uint8_t cnt;
    uint32_t time;
} uartpack;

extern uartpack uart9pack,uart8pack;
extern volatile uartpack uart4pack,uart5pack;
extern uint8_t wtarget,worigin;
extern float speed_forward,target_angle;
extern volatile uint8_t onworking,run_mode;
extern uint8_t username[20],password[20];

void uprintf(uart_ctrl_t *p_ctrl,char *fmt, ...);
void go_to_line1(float speed);
void set_position(uint32_t pos);
void back_to_cross(void);
void turn_to(uint8_t dir);
void go_to_line(uint8_t line);


#endif

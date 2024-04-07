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

#define RunForward 0
#define RunBackward 1
#define RunAngle 2
#define RunIdle 3

#define WORK_IN 1
#define WORK_OUT 2
#define WORK_CH 3

#define TurnLeft 0
#define TurnRight 1


typedef struct 
{
    uint8_t data[256];
    uint8_t len;
    uint8_t cnt;
    uint32_t time;
} uartpack;

extern uartpack uart9pack,uart8pack,uart4pack,uart5pack;
extern uint8_t wtarget,worigin;
extern float speed_forward,target_angle;
extern volatile uint8_t onworking,run_mode;
void uprintf(uart_ctrl_t *p_ctrl,char *fmt, ...);
void go_to_line1(float speed);
void set_position(uint32_t pos);


#endif


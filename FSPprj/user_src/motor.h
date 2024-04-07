#ifndef __motor_H
#define __motor_H

#include "hal_data.h"

#define MOTOR_A 1
#define MOTOR_B 2
#define MOTOR_C 3
#define MOTOR_D 4

void motor_init(void);
void motion_cfg(float vx, float vy,float omega);
void set_fre(uint32_t fre);
void motion_step(uint32_t step,uint8_t dir);
#endif


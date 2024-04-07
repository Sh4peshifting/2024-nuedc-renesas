#ifndef __interface_driver_H
#define __interface_driver_H


#include "user.h"

#define esppack uart8pack
#define esprxc uart8rxc 
#define uart_esp_ctrl g_uart8_ctrl


void esp_init(void);
float read_yaw(void);
void status_upload(void);
void storge_inout(uint8_t *cargo_id,uint8_t *self_id,uint8_t inout);
#endif

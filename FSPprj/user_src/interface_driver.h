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
void get_log(void);
void get_goods(void);
void login_auth(void);
void get_shelf(void);
uint8_t wait_8266return(uint16_t timeout);


#endif

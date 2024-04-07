#ifndef __SCREEN_UART_H__
#define __SCREEN_UART_H__

#include "hal_data.h"
#include <stdio.h>
#include <string.h>

#define SCREEN_UART_HANDLER g_uart9_ctrl
#define OS_DELAY(miliseconds) vTaskDelay(miliseconds) ;

#define SCREEN_RX_HEADER 0x55
#define SCREEN_RX_FOOTER 0xAA
#define SCREEN_RX_CMD_LOGIN 0x00
#define SCREEN_RX_CMD_PUT 0x01
#define SCREEN_RX_CMD_GET 0x02
#define SCREEN_RX_CMD_SWITCH 0x03

#define HIDDEN 0x00
#define VISIBLE 0x01

typedef struct
{
    char alarm_sta[3];
    uint8_t not_empty_shelf;
    uint8_t temperature;
    uint8_t humidity;
} env_info_t;

typedef struct
{
    uint8_t tb_id;
    char shelf_id[6];
    char cargo_id[10];
} shelf_info_t;

typedef struct
{
    char people[10];
    char time[11];
    char operation[10];
    char other_info[10];
} log_info_t;


void update_env_info(env_info_t *env_info);
void shelf_list_insert(shelf_info_t* shelf_info);
void log_list_insert(log_info_t* log_info);
void list_clear(char* list_name);
void screen_login_page_disp(uint8_t is_pwd_correct);
void screen_car_busy_disp(uint8_t is_car_busy);
void screen_rx_proc(uint8_t *screen_rx_buf,uint8_t rx_buf_index);

#endif

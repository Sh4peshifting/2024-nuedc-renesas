#include "screen_uart.h"
#include "FreeRTOS.h"
#include "user.h"

static void user_uart_write(uint8_t const *const p_src, uint32_t const bytes)
{
    R_SCI_UART_Write(&SCREEN_UART_HANDLER, p_src, bytes);
    xSemaphoreTake(uart9txc, portMAX_DELAY);
}

static void change_page(char *page)
{
    char tx_data[20] = {0};
    sprintf(tx_data, "page %s\xff\xff\xff", page);
    user_uart_write((uint8_t *)tx_data, strlen(tx_data));
}

static void change_attribute(char *variable, char *attribute, char *value)
{
    char tx_data[20] = {0};
    sprintf(tx_data, "%s.%s=%s\xff\xff\xff", variable, attribute, value);
    user_uart_write((uint8_t *)tx_data, strlen(tx_data));
}

static void change_visibility(char *variable, char value)
{
    char tx_data[20] = {0};
    sprintf(tx_data, "vis %s,%d\xff\xff\xff", variable, value);
    user_uart_write((uint8_t *)tx_data, strlen(tx_data));
}

void update_env_info(env_info_t *env_info)
{
    char tmp_txt[20];
    sprintf(tmp_txt, "\"%s\"", env_info->alarm_sta);
    change_attribute("alarm_sta", "txt", tmp_txt);
    sprintf(tmp_txt, "\"%d\"", env_info->not_empty_shelf);
    change_attribute("shelf_sta", "txt", tmp_txt);
    sprintf(tmp_txt, "\"%d\"", env_info->temperature);
    change_attribute("temp_sta", "txt", tmp_txt);
    sprintf(tmp_txt, "\"%d\"", env_info->humidity);
    change_attribute("hum_sta", "txt", tmp_txt);
    OS_DELAY(1);
}

void shelf_list_insert(shelf_info_t *shelf_info)
{
    char tx_data[50] = {0};
    sprintf(tx_data, "shelf_list.insert(\"%d^%s^%s\")\xff\xff\xff",
            shelf_info->tb_id, shelf_info->shelf_id, shelf_info->cargo_id);
    user_uart_write((uint8_t *)tx_data, strlen(tx_data));
}

void log_list_insert(log_info_t *log_info)
{
    char tx_data[50] = {0};
    sprintf(tx_data, "log_list.insert(\"%s^%s^%s^%s\")\xff\xff\xff",
            log_info->people, log_info->time, log_info->operation, log_info->other_info);
    user_uart_write((uint8_t *)tx_data, strlen(tx_data));
}

void list_clear(char *list_name)
{
    char tx_data[20] = {0};
    sprintf(tx_data, "%s.clear()\xff\xff\xff", list_name);
    user_uart_write((uint8_t *)tx_data, strlen(tx_data));
}

void screen_login_page_disp(uint8_t is_pwd_correct)
{
    if (is_pwd_correct)
    {
        change_visibility("pwd_err_info", HIDDEN);
        change_page("main");
    }
    else
    {
        change_visibility("pwd_err_info", VISIBLE);
    }
}

void screen_car_busy_disp(uint8_t is_car_busy)
{
    if (is_car_busy)
    {
        change_page("busy_page");
    }
    else
    {
        change_page("main");
    }
}

void screen_rx_proc(uint8_t *screen_rx_buf,uint8_t rx_buf_index)
{
    uint8_t account[10];
    uint8_t passwd[10];
    uint8_t cargo_id[10];
    uint8_t shelf_id[10];
    // uint8_t rx_buf_index = 0;

    // while (screen_rx_buf[rx_buf_index] != 0x00)
    // {
    //     rx_buf_index++;
    // }
    // screen_rx_buf[rx_buf_index] = 0x00;

    if (screen_rx_buf[0] == SCREEN_RX_HEADER)
    {
        switch (screen_rx_buf[1])
        {
        case SCREEN_RX_CMD_LOGIN:
            sscanf((char *)screen_rx_buf + 2, "%s:%s", account, passwd);
            uprintf(&g_uart7_ctrl,"login\n");
            screen_login_page_disp(1);
            
            // login function and use screen_login_page_disp() to display the result
            break;
        case SCREEN_RX_CMD_PUT:
            sscanf((char *)screen_rx_buf + 2, "%s", shelf_id);
            uprintf(&g_uart7_ctrl,"in\n");
            // in storage function
            //read rfid
            storge_inout("None",shelf_id,1);

            break;
        case SCREEN_RX_CMD_GET:
            sscanf((char *)screen_rx_buf + 2, "%s", shelf_id);//待改
            uprintf(&g_uart7_ctrl,"out\n");
            // out storage function
            storge_inout(cargo_id,"None",2);

            break;
        case SCREEN_RX_CMD_SWITCH:
            sscanf((char *)screen_rx_buf + 2, "%s:%s", cargo_id, shelf_id);
            uprintf(&g_uart7_ctrl,"switch\n");
            // switch shelf function
            storge_inout(cargo_id,shelf_id,3);

            break;
        default:
        uprintf(&g_uart7_ctrl,"default\n");
            break;
        }
    }
    memset(screen_rx_buf, 0, rx_buf_index);
}
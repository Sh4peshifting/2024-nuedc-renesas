#include "screen_uart.h"
#include "FreeRTOS.h"
#include "user.h"

static void user_uart_write(uint8_t const *const p_src, uint32_t const bytes)
{
    R_SCI_UART_Write(&SCREEN_UART_HANDLER, p_src, bytes);
    xSemaphoreTake(uart9txc, portMAX_DELAY);
}

void change_page(char *page)
{
    char tx_data[30] = {0};
    sprintf(tx_data, "page %s\xff\xff\xff", page);
    user_uart_write((uint8_t *)tx_data, strlen(tx_data));
}

static void change_attribute(char *variable, char *attribute, char *value)
{
    char tx_data[255] = {0};
    sprintf(tx_data, "%s.%s=%s\xff\xff\xff", variable, attribute, value);
    user_uart_write((uint8_t *)tx_data, strlen(tx_data));
}

static void change_visibility(char *variable, char value)
{
    char tx_data[30] = {0};
    sprintf(tx_data, "vis %s,%d\xff\xff\xff", variable, value);
    user_uart_write((uint8_t *)tx_data, strlen(tx_data));
}

void screen_beep(uint8_t beep_milisec)
{
    char tx_data[20] = {0};
    sprintf(tx_data, "beep %d\xff\xff\xff", beep_milisec);
    user_uart_write((uint8_t *)tx_data, strlen(tx_data));
}

void update_data_list(uint8_t data_type, uint8_t *data_list)
{
    switch (data_type)
    {
    case SCREEN_UPDATE_SHLF_LIST:
        change_attribute("shelf_list", "txt", (char *)data_list);
        break;
    case SCREEN_UPDATE_LOG_LIST:
        change_attribute("log_list", "txt", (char *)data_list);
        break;
    default:
        break;
    }
}

void update_env_info(env_info_t env_info)
{
    char tmp_txt[40];
    sprintf(tmp_txt, "\"%s\"", env_info.alarm_sta);
    change_attribute("alarm_sta", "txt", tmp_txt);
    sprintf(tmp_txt, "\"%d\"", env_info.not_empty_shelf);
    change_attribute("shelf_sta", "txt", tmp_txt);
    sprintf(tmp_txt, "\"%.1f\"", env_info.temperature);
    change_attribute("temp_sta", "txt", tmp_txt);
    sprintf(tmp_txt, "\"%d\"", env_info.humidity);
    change_attribute("hum_sta", "txt", tmp_txt);
    OS_DELAY(1);
}

void update_shelf_info(uint8_t *shelf_status)
{
    if (shelf_status[0] == '1')
    {
        change_attribute("c111", "pic", "2");
        change_attribute("c111", "pic2", "2");
    }
    else
    {
        change_attribute("c111", "pic", "3");
        change_attribute("c111", "pic2", "3");
    }
    if (shelf_status[1] == '1')
    {
        change_attribute("c112", "pic", "2");
        change_attribute("c112", "pic2", "2");
    }
    else
    {
        change_attribute("c112", "pic", "3");
        change_attribute("c112", "pic2", "3");
    }
    if (shelf_status[2] == '1')
    {
        change_attribute("c113", "pic", "2");
        change_attribute("c113", "pic2", "2");
    }
    else
    {
        change_attribute("c113", "pic", "3");
        change_attribute("c113", "pic2", "3");
    }
    if (shelf_status[3] == '1')
    {
        change_attribute("c121", "pic", "2");
        change_attribute("c121", "pic2", "2");
    }
    else
    {
        change_attribute("c121", "pic", "3");
        change_attribute("c121", "pic2", "3");
    }
    if (shelf_status[4] == '1')
    {
        change_attribute("c122", "pic", "2");
        change_attribute("c122", "pic2", "2");
    }
    else
    {
        change_attribute("c122", "pic", "3");
        change_attribute("c122", "pic2", "3");
    }
    if (shelf_status[5] == '1')
    {
        change_attribute("c123", "pic", "2");
        change_attribute("c123", "pic2", "2");
    }
    else
    {
        change_attribute("c123", "pic", "3");
        change_attribute("c123", "pic2", "3");
    }
}

static char *get_inout_shelf_id(uint8_t *recv_data)
{
    if (recv_data[0] == 0x01)
        return "1-1-1";
    else if (recv_data[1] == 0x01)
        return "1-1-2";
    else if (recv_data[2] == 0x01)
        return "1-1-3";
    else if (recv_data[3] == 0x01)
        return "1-2-1";
    else if (recv_data[4] == 0x01)
        return "1-2-2";
    else if (recv_data[5] == 0x01)
        return "1-2-3";
    else
        return "0";
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

void screen_error_msg_disp(uint8_t is_error)
{
    if (is_error)
    {
        change_page("err_info");
    }
    else
    {
        change_page("main");
    }

}

void screen_rx_proc(uint8_t *screen_rx_buf, uint8_t rx_buf_index)
{
    uint8_t account[20];
    uint8_t passwd[20];
    // uint8_t cargo_id[10];
    uint8_t old_shelf_id[10];
    uint8_t shelf_id[10];

    screen_rx_buf[rx_buf_index - 1] = 0x00;

    if (screen_rx_buf[0] == SCREEN_RX_HEADER)
    {
        switch (screen_rx_buf[1])
        {
        case SCREEN_RX_CMD_LOGIN:
            sscanf((char *)screen_rx_buf + 2, "%s %s", account, passwd);
            uprintf(&g_uart7_ctrl, "login\n");
            
            strcpy((char *)username, (char *)account);
            strcpy((char *)password, (char *)passwd);
            
            uprintf(&g_uart7_ctrl, "username:%s\n", account);
            uprintf(&g_uart7_ctrl,"password:%s\n", passwd);

            login_auth();
            // screen_login_page_disp(1);
            // login function and use screen_login_page_disp() to display the result
            break;
        case SCREEN_RX_CMD_PUT:
            sscanf(get_inout_shelf_id(screen_rx_buf + 2), "%s", shelf_id);
            uprintf(&g_uart7_ctrl, "in\n");
            // in storage function
            // read rfid
            storge_inout((uint8_t *)"None", shelf_id, 4);
            get_shelf();

            break;
        case SCREEN_RX_CMD_GET:
            sscanf(get_inout_shelf_id(screen_rx_buf + 2), "%s", shelf_id); 
            uprintf(&g_uart7_ctrl, "out\n");
            // out storage function
            storge_inout((uint8_t *)"None", shelf_id, 2);//need to modify
            get_shelf();

            break;
        case SCREEN_RX_CMD_SWITCH:
            // sscanf((char *)screen_rx_buf + 2, "%s %s", cargo_id, shelf_id);
            sscanf((char *)screen_rx_buf + 2, "%5s %5s", old_shelf_id, shelf_id);
            uprintf(&g_uart7_ctrl, "switch\n");
            // switch shelf function
            storge_inout(shelf_id, old_shelf_id, 3);//need to modify

            break;
        case SCREEN_RX_CMD_SHELF_LIST:
            // update shelf list
            uprintf(&g_uart7_ctrl, "get good list\n");
            get_goods();
            break;
        case SCREEN_RX_CMD_LOG_LIST:
            // update log list
            uprintf(&g_uart7_ctrl, "get log\n");
            get_log();

            break;
        case SCREEN_UPDATE_SHELF_INFO:
            // update shelf info
            uprintf(&g_uart7_ctrl, "get shelf\n");
            get_shelf();

            break;
        default:
            uprintf(&g_uart7_ctrl, "default\n");
            break;
        }
    }
    // memset(screen_rx_buf, 0, rx_buf_index);
}

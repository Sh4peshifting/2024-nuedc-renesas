#include "interface_driver.h"
#include "user.h"

uint8_t wtarget,worigin,islogin; 
int light_status;

uint8_t wait_8266return(uint16_t timeout)
{
    if(xSemaphoreTake(esprxc,timeout)==pdFALSE){
        uprintf(&g_uart7_ctrl,"wait 8266 return overtime\n");
        return 1;
    }
    else{
        return 0;
    }
}
void esp_init(void)
{
    xSemaphoreTake(on8266,portMAX_DELAY);
    while(!strstr((const char *)uart8pack.data,"WIFI GOT IP")){
        uprintf(&g_uart7_ctrl,"Connecting...\n");
        if(1==wait_8266return(6000)){
            uprintf(&g_uart7_ctrl,"Connecting failed\nReseting...\n");
            uprintf(&g_uart8_ctrl,"+++");//退出透传
            vTaskDelay(1000);
            uprintf(&g_uart8_ctrl,"AT+RST\r\n");
        }

    }

    uprintf(&g_uart8_ctrl,"ATE0\r\n");
    wait_8266return(3000);

    uprintf(&g_uart8_ctrl,"AT+CIPSTART=\"TCP\",\"wms.hizrd.top\",17200\r\n");
    wait_8266return(3000);

    uprintf(&g_uart8_ctrl,"AT+CIPMODE=1\r\n");
    wait_8266return(3000);

    uprintf(&g_uart8_ctrl,"AT+CIPSEND\r\n");
    wait_8266return(3000);

    xSemaphoreGive(on8266);

    uprintf(&g_uart7_ctrl,"esp init success\n");

}

void reconnect_server(void)
{
    uprintf(&g_uart8_ctrl,"GET /index/\r\n\r\n");
    if(!wait_8266return(3000)){
        uart8pack.data[uart8pack.len] = 0;
        if (strstr((const char *)uart8pack.data, "hello")){
            return;
        }
        else{
        }
    }

    uprintf(&g_uart8_ctrl,"AT+RST\r\n");
    while (!strstr((const char *)uart8pack.data, "WIFI GOT IP"))
    {
        uprintf(&g_uart7_ctrl, "Connecting...\n");
        if (1 == wait_8266return(6000))
        {
            uprintf(&g_uart7_ctrl, "Connecting failed\nReseting...\n");
            uprintf(&g_uart8_ctrl, "+++"); // 退出透传
            vTaskDelay(1000);
            uprintf(&g_uart8_ctrl, "AT+RST\r\n");
        }
    }
    uprintf(&g_uart8_ctrl,"ATE0\r\n");
    wait_8266return(3000);
    uprintf(&g_uart8_ctrl,"AT+CIPSTART=\"TCP\",\"wms.hizrd.top\",17200\r\n");
    wait_8266return(3000);
    uprintf(&g_uart8_ctrl,"AT+CIPMODE=1\r\n");
    wait_8266return(3000);
    uprintf(&g_uart8_ctrl,"AT+CIPSEND\r\n");
    wait_8266return(3000);

    uprintf(&g_uart7_ctrl,"esp restart success\n");
}
float read_yaw(void)
{
	return (float)((uart5pack.data[29]<<8)+uart5pack.data[28])/32768*180;
}

void status_upload(void)
{
    static env_info_t env_info;
    DHT11_Data_TypeDef dht11_data;
    int l_worigin,l_wtarget,l_onworking,not_empty_shelf;
    static uint8_t last_work=0;

    vTaskSuspendAll();
    Read_DHT11(&dht11_data);
    xTaskResumeAll();

    fire_status_t onfire = fire_detect();
    
    xSemaphoreTake(on8266,portMAX_DELAY);
    vTaskDelay(20);
    
    uprintf(&uart_esp_ctrl,"GET /interface/sensor/?humi=%d&temp=%d.%d&fire=%d&working=%d\r\n\r\n",
        dht11_data.humi_int,dht11_data.temp_int,dht11_data.temp_deci,onfire,onworking);
    if(wait_8266return(2000)){
        reconnect_server();
        goto esperror;
    }
    // R_SCI_UART_Write(&g_uart7_ctrl,uart8pack.data,uart8pack.len);
    // xSemaphoreTake(uart7txc,portMAX_DELAY);
    uart8pack.data[uart8pack.len]=0;
    if(strstr((const char *)uart8pack.data,"ERROR")){
        reconnect_server();
        goto esperror;
    }
    // #define WORK_IN 1
    // #define WORK_OUT 2
    // #define WORK_CH 3
    //L2关,1开,0无操作
    //传递运行命令
    sscanf(uart8pack.data,"L:%d,Origin:%d,Target:%d,Work:%d,Vacant:%d,",
    &light_status,&l_worigin,&l_wtarget,&l_onworking,&not_empty_shelf);

    env_info.temperature = (float)dht11_data.temp_int+(float)dht11_data.temp_deci/10;
    env_info.humidity = dht11_data.humi_int;
    if(onfire==FIRE_DETECTED) {
        memcpy(env_info.alarm_sta,"报警",7);
        screen_beep(200);
    }
    else  memcpy(env_info.alarm_sta,"正常",7);

    if(l_onworking!=WORK_IDLE){
        worigin=(uint8_t)l_worigin;
        wtarget=(uint8_t)l_wtarget;
        onworking=(uint8_t)l_onworking;
    }

    if(last_work!=onworking){
        last_work=onworking;
        if(onworking==WORK_IDLE){
            if(islogin) change_page("main");
            else change_page("sign_in");
        }
        else{
            change_page("busy_page");
        }
    }

    if(99 != not_empty_shelf){
        env_info.not_empty_shelf = (uint8_t)not_empty_shelf;
    }
    update_env_info(env_info);

esperror:
    xSemaphoreGive(on8266);//把串口屏操作也放在8266互斥锁中

}

void login_auth()
{
    xSemaphoreTake(on8266,portMAX_DELAY);
    vTaskDelay(20);
    uprintf(&uart_esp_ctrl,"GET /interface/login/?username=%s&password=%s\r\n\r\n",username,password);
    if(!wait_8266return(2000)){
        uart8pack.data[uart8pack.len] = 0;
        if(strstr((const char *)uart8pack.data,"success")){
            // 登录成功
            screen_login_page_disp(1);
            islogin=1;
        }
        else{
            // 登录失败 弹窗
            screen_login_page_disp(0);
            islogin=0;
        }

    }
    xSemaphoreGive(on8266);
}

// inout: in1 out2 change3
void storge_inout(uint8_t *cargo_id,uint8_t *self_id,uint8_t inout)
{
    xSemaphoreTake(on8266,portMAX_DELAY);
    vTaskDelay(20);

    xSemaphoreTake(uart8rxc,0);
    uprintf(&uart_esp_ctrl,"GET /interface/cargo/?cargo_id=%s&self_id=%s&in=%d&username=%s&password=%s\r\n\r\n",
    cargo_id,self_id,inout,username,password);

    if(!wait_8266return(2000))
    {
        uart8pack.data[uart8pack.len] = 0;
        if (strstr((const char *)uart8pack.data, "success"))
        {
            // 申请成功
        }
        else
        {
            // 操作失败 弹窗
            screen_error_msg_disp(1);
        }
    }

    xSemaphoreGive(on8266);
}

void storge_inout11(uint8_t *cargo_id,uint8_t self_id,uint8_t inout,uint8_t username)
{
    xSemaphoreTake(on8266,portMAX_DELAY);
    vTaskDelay(20);

    xSemaphoreTake(uart8rxc,0);
    uprintf(&uart_esp_ctrl,"GET /interface/cargo/?cargo_id=%s&self_id=%d&in=%d&username=%d&password=000\r\n\r\n",
    cargo_id,self_id,inout,username);

    if(!wait_8266return(2000))
    {
    }

    xSemaphoreGive(on8266);
}

void storge_inout112(uint8_t *cargo_id,uint8_t self_id,uint8_t inout,uint8_t username)
{
    uint8_t nn=2;
    xSemaphoreTake(on8266,portMAX_DELAY);
    vTaskDelay(20);
    xSemaphoreTake(uart8rxc,0);
retx8266:
    uprintf(&uart_esp_ctrl,"GET /interface/cargo/?cargo_id=%s&self_id=%d&in=%d&username=%d&password=000\r\n\r\n",
    cargo_id,self_id,inout,username);

    if(!wait_8266return(2000))
    {
    }
    else{
        if(nn){
            nn--;
            goto retx8266;
        }

    }

    xSemaphoreGive(on8266);
}


void get_log()
{
    xSemaphoreTake(on8266,portMAX_DELAY);
    vTaskDelay(20);
    uprintf(&g_uart8_ctrl,"GET /interface/get_log/\r\n\r\n");
    if(!wait_8266return(2000)){
        R_SCI_UART_Write(&g_uart7_ctrl,uart8pack.data,uart8pack.len);
        xSemaphoreTake(uart7txc,portMAX_DELAY);
        esppack.data[esppack.len]=0;
        update_data_list(SCREEN_UPDATE_LOG_LIST,esppack.data);
    }

    xSemaphoreGive(on8266);
}

void get_goods()
{
    xSemaphoreTake(on8266,portMAX_DELAY);
    vTaskDelay(20);
    uprintf(&g_uart8_ctrl,"GET /interface/get_goods/\r\n\r\n");
    if(!wait_8266return(2000)){
        // R_SCI_UART_Write(&g_uart7_ctrl,uart8pack.data,uart8pack.len);
        // xSemaphoreTake(uart7txc,portMAX_DELAY);
        esppack.data[esppack.len]=0;
        update_data_list(SCREEN_UPDATE_SHLF_LIST,esppack.data);
    }
    
    xSemaphoreGive(on8266);
}

void get_shelf()
{
    xSemaphoreTake(on8266,portMAX_DELAY);
    vTaskDelay(20);
    uprintf(&g_uart8_ctrl,"GET /interface/shelf/\r\n\r\n");
    if(!wait_8266return(2000)){
        // R_SCI_UART_Write(&g_uart7_ctrl,uart8pack.data,uart8pack.len);
        // xSemaphoreTake(uart7txc,portMAX_DELAY);
        esppack.data[esppack.len]=0;
        update_shelf_info(esppack.data);
    }
    
    xSemaphoreGive(on8266);
}
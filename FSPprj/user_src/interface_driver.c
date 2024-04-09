#include "interface_driver.h"
#include "user.h"

uint8_t wtarget,worigin; 

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
        wait_8266return(10000);

    }

    uprintf(&g_uart8_ctrl,"ATE0\r\n");
    wait_8266return(3000);

    uprintf(&g_uart8_ctrl,"AT+CIPSTART=\"TCP\",\"192.168.100.166\",8000\r\n");
    wait_8266return(3000);

    uprintf(&g_uart8_ctrl,"AT+CIPMODE=1\r\n");
    wait_8266return(3000);

    uprintf(&g_uart8_ctrl,"AT+CIPSEND\r\n");
    wait_8266return(3000);

    xSemaphoreGive(on8266);

    uprintf(&g_uart7_ctrl,"esp init success\n");

}

float read_yaw(void)
{
	return (float)((uart5pack.data[7]<<8)+uart5pack.data[6])/32768*180;
}

void status_upload(void)
{
    DHT11_Data_TypeDef dht11_data;
    uint8_t light_status;
    uint8_t l_worigin,l_wtarget,l_onworking,not_empty_shelf;
    Read_DHT11(&dht11_data);
    fire_status_t onfire=fire_detect();

    xSemaphoreTake(on8266,portMAX_DELAY);
    vTaskDelay(10);

    uprintf(&uart_esp_ctrl,"GET /interface/sensor/?humi=%d&temp=%d.%d&fire=%d&working=%d\r\n\r\n",
        dht11_data.humi_int,dht11_data.temp_int,dht11_data.temp_deci,onfire,onworking);
    if(wait_8266return(500)){
        return;
    }

    //process website cmd
    uart8pack.data[uart8pack.len]=0;
    sscanf((const char *)uart8pack.data,"L:%d,Origin:%d,Target:%d,Work:%d,Vacant:%d,\r\n",
    (int *)&light_status,(int *)&l_worigin,(int *)&l_wtarget,(int *)&l_onworking,(int *)&not_empty_shelf);
    // #define WORK_IN 1
    // #define WORK_OUT 2
    // #define WORK_CH 3
    //L2关,1开,0无操作
    //传递运行命令
    if(light_status){
        if(light_status==1) light_ctrl(LIGHT_ON);
        else if(light_status==2) light_ctrl(LIGHT_OFF);
        else ;
    }

    if(l_onworking!=WORK_IDLE){
        worigin=l_worigin;
        wtarget=l_wtarget;
        onworking=l_onworking;
    }

    xSemaphoreGive(on8266);

    env_info_t env_info={("55"),not_empty_shelf,dht11_data.temp_int,dht11_data.humi_int};//未解决
    //env_info_t env_info={"45",5,15,15};
    update_env_info(&env_info);


}

void login_auth()
{
    xSemaphoreTake(on8266,portMAX_DELAY);



    xSemaphoreGive(on8266);
}

// inout: in1 out2 change3
void storge_inout(uint8_t *cargo_id,uint8_t *self_id,uint8_t inout)
{
    xSemaphoreTake(on8266,portMAX_DELAY);
    xSemaphoreTake(uart8rxc,0);
    uprintf(&uart_esp_ctrl,"GET /interface/cargo/?cargo_id=%s&self_id%s&in=%d\r\n",cargo_id,self_id,inout);
    xSemaphoreTake(uart8rxc,portMAX_DELAY);

    uart8pack.data[uart8pack.len]=0;
    if(strstr((const char *)uart8pack.data,"success")){
        //申请成功
    }
    else {
        //操作失败 弹窗
        screen_error_msg_disp(1);
    }

    xSemaphoreGive(on8266);
}

void get_log()
{
    xSemaphoreTake(on8266,portMAX_DELAY);

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
    vTaskDelay(10);
    uprintf(&g_uart8_ctrl,"GET /interface/get_goods/\r\n\r\n");
    if(!wait_8266return(2000)){
        R_SCI_UART_Write(&g_uart7_ctrl,uart8pack.data,uart8pack.len);
        xSemaphoreTake(uart7txc,portMAX_DELAY);
        esppack.data[esppack.len]=0;
        update_data_list(SCREEN_UPDATE_SHLF_LIST,esppack.data);
    }
    
    xSemaphoreGive(on8266);
}
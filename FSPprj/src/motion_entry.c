#include "motion.h"
#include "user.h"

float pid_track(float target, float current)
{	
	float limit=3,kp=0,kd=0;
	float bias;  
	static float output,last_bais;
	bias=target-current; //求偏差
	output=kp*bias+kd*(bias-last_bais);  //位置式PD控制器																									 
	last_bais=bias;
	if(output>limit)
	{
		output=limit;
	}
	if(output<-limit)
	{
		output=-limit;
	}
	return output;
}

float pid_angle(float target, float current)
{	
	float limit=3,kp=0,kd=0;
	float bias,output;  
	static float last_bais;
	bias=target-current; //求偏差
	if (bias >= 180)
	{
		bias -= 360;
	}
	if (bias <= -180)
	{
		bias += 360;
	}

	output=kp*bias+kd*(bias-last_bais);  //位置式PD控制器																									 
	last_bais=bias;
	if(output>limit)
	{
		output=limit;
	}
	if(output<-limit)
	{
		output=-limit;
	}
	return output;
}


/* motion entry function */
/* pvParameters contains TaskHandle_t */
void motion_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);

    /* TODO: add your own code here */
    while (1)
    {
        if(run_mode==RunForward){
            xSemaphoreTake(uart4rxc,portMAX_DELAY);
            float omega=pid_angle(128,uart4pack.data[4]);
            float vy=pid_track(128,uart4pack.data[3]);
            motion_cfg(speed_forward,vy,omega);

        }
        else if(run_mode == RunAngle){
            xSemaphoreTake(uart5rxc,portMAX_DELAY);
            float omega=pid_angle(target_angle,read_yaw());
            motion_cfg(0,0,omega);
        }
        else if(run_mode == RunIdle){
            
        }
       
        vTaskDelay(5);
    }
}

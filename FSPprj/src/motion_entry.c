#include "motion.h"
#include "user.h"
#include "foc_utils.h"
float pid_track(float target, float current)
{	
	float limit=0.3f,kp=0.009f,kd=0;
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
	float limit=0.2f,kp=0.009f,kd=0.00001f;
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

void limit(float *a,float limit)
{
	if(*a>limit)
	{
		*a=limit;
	}
	if(*a<-limit)
	{
		*a=-limit;
	}
}
/* motion entry function */
/* pvParameters contains TaskHandle_t */
void motion_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);
	
    /* TODO: add your own code here */
	motor_init();
	run_mode=RunIdle;
	// xSemaphoreTake(uart5rxc,portMAX_DELAY);
	// motion_cfg(-0.3f,0,0);
	// target_angle=read_yaw();
    while (1)
    {
        if(run_mode==RunForward){
            xSemaphoreTake(uart4rxc,portMAX_DELAY);
            float omega=pid_angle(128,uart4pack.data[4]);
			float vd,vq;
			vq=pid_track(128,uart4pack.data[3]);//track
			motion_cfgground(speed_forward,-vq,128-uart4pack.data[4],omega);

        }
        else if(run_mode == RunAngle){
            xSemaphoreTake(uart5rxc,portMAX_DELAY);
            float omega=pid_angle(target_angle,read_yaw());
            motion_cfg(0,0,omega);
        }
        else if(run_mode == RunIdle){
            speed_forward=0;
			motion_cfg(0,0,0);
        }
		else if(run_mode== RunVt){
			xSemaphoreTake(uart5rxc,portMAX_DELAY);
			motion_cfg2(0.3f,read_yaw(),0.2f);
		}
       
        vTaskDelay(5);
    }
}

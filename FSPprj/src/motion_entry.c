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
	run_mode=RunForward;
	// xSemaphoreTake(uart5rxc,portMAX_DELAY);
	// motion_cfg(-0.3f,0,0);
	// target_angle=read_yaw();
    while (1)
    {
        if(run_mode==RunForward){
            xSemaphoreTake(uart4rxc,portMAX_DELAY);
            float omega=pid_angle(128,uart4pack.data[4]);
			// R_SCI_UART_Write(&g_uart7_ctrl,uart4pack.data,uart4pack.len);
			// xSemaphoreTake(uart7txc,portMAX_DELAY);
            // float vy=pid_track(128,uart4pack.data[3]);
			
			

			float vd,vq,vx,vy,alpha;

			// vd=0;
			vq=pid_track(128,uart4pack.data[3]);//track
			// alpha = uart4pack.data[4]-128;
			// vx=vd*_cos(alpha)-vq*_sin(alpha);
			// vy=-(vd*_sin(alpha)+vq*_cos(alpha));
			
			// limit(&vx,0.3f);
			// limit(&vy,0.3f);
			// motion_cfg(vx,vy,0);
            // motion_cfg(speed_forward,vy,omega);
			// motion_cfg(0,0,omega);

			float increase;
			uprintf(&g_uart7_ctrl,"vq:%.2f increase:%.2f\n",vq,increase);
			float vqqq=_sqrtApprox(vq*vq+0.04f);
			// motion_cfg2(vq,uart4pack.data[4]-128+90,omega);
			motion_cfg2(vqqq,uart4pack.data[4]-128+atan2f(vq,0.2f),omega);

        }
        else if(run_mode == RunAngle){
            xSemaphoreTake(uart5rxc,portMAX_DELAY);
            float omega=pid_angle(target_angle,read_yaw());
            motion_cfg(0,0,omega);
        }
        else if(run_mode == RunIdle){
            
        }
		else if(run_mode== RunVt){
			xSemaphoreTake(uart5rxc,portMAX_DELAY);
			motion_cfg2(0.3f,read_yaw(),0.2f);
		}
       
        vTaskDelay(5);
    }
}

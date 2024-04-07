#include "motor.h"

volatile uint32_t step_cnt=0;

void motor_init()
{
    R_GPT_Open(g_timer4.p_ctrl,g_timer4.p_cfg);//step motor
    R_GPT_Open(g_timer5.p_ctrl,g_timer5.p_cfg);
    R_GPT_Open(g_timer6.p_ctrl,g_timer6.p_cfg);
    motion_cfg(0,0,0);
    R_GPT_Start(g_timer5.p_ctrl);
    R_GPT_Start(g_timer6.p_ctrl);
}

void set_pwm(timer_ctrl_t * const p_ctrl,uint32_t const pin, float duty)
{
    timer_info_t info;
    R_GPT_InfoGet(p_ctrl, &info);
    uint32_t current_period_counts = info.period_counts;
    uint32_t duty_cycle_counts =(uint32_t) ((float)current_period_counts * duty);
    R_GPT_DutyCycleSet(p_ctrl, duty_cycle_counts, pin);
}

void motor_cfg(uint8_t motor,float duty)
{
    if(motor == MOTOR_A){
        if(duty>0){
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_a1,BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_a2,BSP_IO_LEVEL_HIGH);   
        }
        else if(duty<0){
            duty=-duty;
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_a1,BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_a2,BSP_IO_LEVEL_HIGH);
        }
        else{
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_a1,BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_a2,BSP_IO_LEVEL_HIGH);
        }
           
        set_pwm(g_timer5.p_ctrl,GPT_IO_PIN_GTIOCB,duty);
    }
   else if(motor == MOTOR_B){
        if(duty>0){
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_b1,BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_b2,BSP_IO_LEVEL_HIGH);
        }
        else if(duty<0){
            duty=-duty;
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_b1,BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_b2,BSP_IO_LEVEL_HIGH);
        }
        else{
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_b1,BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_b2,BSP_IO_LEVEL_HIGH);
        }
        set_pwm(g_timer5.p_ctrl,GPT_IO_PIN_GTIOCA,duty);
    }
   else if(motor == MOTOR_C){
        if(duty>0){
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_c1,BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_c2,BSP_IO_LEVEL_HIGH);
        }
        else if(duty<0){
            duty=-duty;
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_c1,BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_c2,BSP_IO_LEVEL_HIGH);
        }
        else{
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_c1,BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_c2,BSP_IO_LEVEL_HIGH);
        }
        set_pwm(g_timer6.p_ctrl,GPT_IO_PIN_GTIOCB,duty);
    }
   else if(motor == MOTOR_D){
        if(duty>0){
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_d1,BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_d2,BSP_IO_LEVEL_HIGH);
        }
        else if(duty<0){
            duty=-duty;
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_d1,BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_d2,BSP_IO_LEVEL_HIGH);
        }
        else{
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_d1,BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(g_ioport.p_ctrl,m_d2,BSP_IO_LEVEL_HIGH);
        }
        set_pwm(g_timer6.p_ctrl,GPT_IO_PIN_GTIOCA,duty);
    }
}

void motion_cfg(float vx, float vy,float omega)
{
    float omegaprxpry=omega*2;
    float duty1,duty2,duty3,duty4;
    duty1=vx-vy-omegaprxpry;
    duty2=vx+vy+omegaprxpry;
    duty3=vx+vy-omegaprxpry;
    duty4=vx-vy+omegaprxpry;
    
    motor_cfg(1,duty1);
    motor_cfg(2,duty2);
    motor_cfg(3,duty3);
    motor_cfg(4,duty4);
    
}

void motion_step(uint16_t step,uint8_t dir)
{
    step_cnt=step;
    set_fre(5000);
    R_GPT_Start(&g_timer4_ctrl);
    if(dir)R_IOPORT_PinWrite(&g_ioport_ctrl,step_dir,1);
    else R_IOPORT_PinWrite(&g_ioport_ctrl,step_dir,0);
    uint32_t fre=5000;
    while(step_cnt){
        set_fre(fre);
        fre>=30000?(void)0:(fre+=1000);
        if(step>3000);
        else if(step>2000 && fre>15000)fre=15000;
        else if(step>1000 && fre>5000 )fre=5000;
        vTaskDelay(20);
    }
}

void gpt4_callback(timer_callback_args_t * p_args)
{
    if(p_args->event == TIMER_EVENT_CYCLE_END ){
        step_cnt--;
        if(step_cnt == 0){
            R_GPT_Stop(&g_timer4_ctrl);
        }

    }
}

void set_fre(uint32_t fre)
{
    uint32_t pclkd_freq_hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKD) >> g_timer4_cfg.source_div;
    uint32_t period_counts =
        (uint32_t) ( pclkd_freq_hz / fre);
    /* Set the calculated period. */
    R_GPT_PeriodSet(&g_timer4_ctrl, period_counts);
}
#include "working.h"
#include "user.h"

void run_in(void);
void run_out(void);
void run_change(void);
/* working entry function */
/* pvParameters contains TaskHandle_t */
void working_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);

    /* TODO: add your own code here */
    while (1)
    {
        if(onworking == WORK_IN){
            set_position(_pos_mm(20));
            back_to_cross(1);
            set_position(_pos_mm(0));
            onworking=WORK_IDLE;

        }
        else if(onworking == WORK_OUT){
            back_to_cross(3);
            onworking=WORK_IDLE;

        }
        else if(onworking == WORK_CH){

        }
        else if(onworking == 0){
            
        }
        else{

        }
        vTaskDelay(10);
    }
}


void run_in()
{
    go_to_line1(0.5f);
    go_to_line1(0.2f);
    set_position(1);
    back_to_cross(1);

    turn_to(TurnRight);

    go_to_line(wtarget > 3 ? wtarget : wtarget - 3);

    turn_to(TurnLeft);

    set_position(2);

    go_to_line1(0.2f);

    back_to_cross(1);

    turn_to(TurnLeft);

    go_to_line(wtarget > 3 ? wtarget : wtarget - 3);


    turn_to(TurnRight);

    back_to_cross(1);

    onworking = WORK_IDLE;
}


void run_out()
{

}

void go_to_enter(void)
{   
    back_to_cross(1);
    
}
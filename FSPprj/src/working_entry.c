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

        }
        else if(onworking == WORK_OUT){

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

    back_to_cross();
    
}


void run_out()
{

}
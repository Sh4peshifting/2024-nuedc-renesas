#include "working.h"
#include "user.h"

void run_in(void);
void run_out(void);
void run_change(void);
void run_prein(void);
/* working entry function */
/* pvParameters contains TaskHandle_t */
void working_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);

    /* TODO: add your own code here */
    ic_detect_init();
    while (1)
    {
        if(onworking == WORK_IN){
            run_in();
        }
        else if(onworking == WORK_OUT){
            run_out();
        }
        else if(onworking == WORK_CH){
            run_change();
        }
        else if(onworking == WORK_IDLE){
            
        }
        else if(onworking == WORK_PREIN){
            run_prein();
        }
        else{

        }
        vTaskDelay(10);
    }
}


void run_in()
{
    set_position(_pos_mm(STEP_F1_LIFT));
    back_to_cross(1+(wtarget <= 3 ? wtarget : wtarget - 3));
    turn_to(TurnRight);
    if(wtarget>3) set_position(_pos_mm(STEP_F2_LIFT));
    go_to_cross(1);
    run_mode=RunAlign;
    vTaskDelay(1000);
    if (wtarget <= 3)
        set_position(_pos_mm(STEP_F1));
    else
        set_position(_pos_mm(STEP_F2));
    back_to_cross(1);
    turn_to(TurnRight);
    back_to_cross(wtarget <= 3 ? wtarget : wtarget - 3);
    turn_to(TurnRight);
    go_to_cross(1);
    run_mode=RunAlign;
    vTaskDelay(1400);
    run_mode = RunIdle;
    onworking=WORK_IDLE;
}


void run_out()
{
    back_to_cross(1);
    turn_to(TurnRight);
    back_to_cross(wtarget <= 3 ? wtarget : wtarget - 3);
    turn_to(TurnRight);
    if(wtarget>3) set_position(_pos_mm(STEP_F2));
    go_to_cross(1);
    run_mode=RunAlign;
    vTaskDelay(1000);
    if(wtarget<=3)
        set_position(_pos_mm(STEP_F1_LIFT));
    else
        set_position(_pos_mm(STEP_F2_LIFT));
    back_to_cross(1);
    turn_to(TurnRight);
    back_to_cross(wtarget <= 3 ? wtarget : wtarget - 3);
    turn_to(TurnBack);
    
    go_to_cross(1);
    run_mode=RunAlign;

    set_position(_pos_mm(STEP_F1));
    back_to_cross(1);
    turn_to(TurnLeft);

    go_to_cross(1);
    run_mode=RunAlign;
    vTaskDelay(1400);
    run_mode = RunIdle;
    onworking=WORK_IDLE;
}


void run_prein(void)
{
    uint8_t card_id[5]={0};
    back_to_cross(1);
    turn_to(TurnRight);

    go_to_cross(1);

    run_mode=RunAlign;
    vTaskDelay(1300);
    
    uint8_t status=read_card_pro(card_id);
    if(status){
        onworking=WORK_IDLE;
        back_to_cross(1);
        turn_to(TurnLeft);
        go_to_cross(1);
        run_mode = RunAlign;
        vTaskDelay(1400);
        run_mode = RunIdle;
        onworking = WORK_IDLE;
    }
    else{
        char id[12];

        sprintf(id,"%02x%02x%02x%02x",card_id[0],card_id[1],card_id[2],card_id[3]);
        storge_inout11(id, wtarget,11,worigin);
        onworking = WORK_IDLE;
    }

}
uint8_t normalization_num(uint8_t number)
{
    if(number>3) return number-3;
    else return number;
}
void run_change(void)
{
    back_to_cross(1);
    turn_to(TurnRight);
    back_to_cross(worigin <= 3 ? worigin : worigin - 3);
    turn_to(TurnRight);
    if(worigin>3) set_position(_pos_mm(STEP_F2));
    go_to_cross(1);
    run_mode=RunAlign;
    vTaskDelay(1000);
    if(worigin<=3)
        set_position(_pos_mm(STEP_F1_LIFT));
    else
        set_position(_pos_mm(STEP_F2_LIFT));
    back_to_cross(1);

    int translation= normalization_num(wtarget) - normalization_num(worigin);
    if(translation<0) slide_to_line(SlideLeft, -translation+1);
    else slide_to_line(SlideRight,translation+1);

    if(wtarget<=3)
        set_position(_pos_mm(STEP_F1_LIFT));
    else
        set_position(_pos_mm(STEP_F2_LIFT));
    
    go_to_cross(1);
    run_mode=RunAlign;
    vTaskDelay(1000);

    if(wtarget<=3)
        set_position(_pos_mm(STEP_F1));
    else
        set_position(_pos_mm(STEP_F2));

    
    back_to_cross(1);
    turn_to(TurnRight);
    back_to_cross(wtarget <= 3 ? wtarget : wtarget - 3);
    turn_to(TurnRight);
    go_to_cross(1);
    run_mode=RunAlign;
    vTaskDelay(1400);
    run_mode = RunIdle;
    onworking=WORK_IDLE;
    

}


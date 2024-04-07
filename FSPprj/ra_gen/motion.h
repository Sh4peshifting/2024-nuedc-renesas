/* generated thread header file - do not edit */
#ifndef MOTION_H_
#define MOTION_H_
#include "bsp_api.h"
                #include "FreeRTOS.h"
                #include "task.h"
                #include "semphr.h"
                #include "hal_data.h"
                #ifdef __cplusplus
                extern "C" void motion_entry(void * pvParameters);
                #else
                extern void motion_entry(void * pvParameters);
                #endif
FSP_HEADER
FSP_FOOTER
#endif /* MOTION_H_ */

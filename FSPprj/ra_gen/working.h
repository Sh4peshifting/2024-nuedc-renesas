/* generated thread header file - do not edit */
#ifndef WORKING_H_
#define WORKING_H_
#include "bsp_api.h"
                #include "FreeRTOS.h"
                #include "task.h"
                #include "semphr.h"
                #include "hal_data.h"
                #ifdef __cplusplus
                extern "C" void working_entry(void * pvParameters);
                #else
                extern void working_entry(void * pvParameters);
                #endif
FSP_HEADER
FSP_FOOTER
#endif /* WORKING_H_ */

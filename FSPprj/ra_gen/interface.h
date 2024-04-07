/* generated thread header file - do not edit */
#ifndef INTERFACE_H_
#define INTERFACE_H_
#include "bsp_api.h"
                #include "FreeRTOS.h"
                #include "task.h"
                #include "semphr.h"
                #include "hal_data.h"
                #ifdef __cplusplus
                extern "C" void interface_entry(void * pvParameters);
                #else
                extern void interface_entry(void * pvParameters);
                #endif
FSP_HEADER
FSP_FOOTER
#endif /* INTERFACE_H_ */

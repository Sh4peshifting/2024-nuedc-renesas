/* generated thread header file - do not edit */
#ifndef HMI_H_
#define HMI_H_
#include "bsp_api.h"
                #include "FreeRTOS.h"
                #include "task.h"
                #include "semphr.h"
                #include "hal_data.h"
                #ifdef __cplusplus
                extern "C" void hmi_entry(void * pvParameters);
                #else
                extern void hmi_entry(void * pvParameters);
                #endif
FSP_HEADER
FSP_FOOTER
#endif /* HMI_H_ */

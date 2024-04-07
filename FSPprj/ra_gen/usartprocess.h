/* generated thread header file - do not edit */
#ifndef USARTPROCESS_H_
#define USARTPROCESS_H_
#include "bsp_api.h"
                #include "FreeRTOS.h"
                #include "task.h"
                #include "semphr.h"
                #include "hal_data.h"
                #ifdef __cplusplus
                extern "C" void usartprocess_entry(void * pvParameters);
                #else
                extern void usartprocess_entry(void * pvParameters);
                #endif
FSP_HEADER
FSP_FOOTER
#endif /* USARTPROCESS_H_ */

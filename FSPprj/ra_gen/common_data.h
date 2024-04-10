/* generated common header file - do not edit */
#ifndef COMMON_DATA_H_
#define COMMON_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "FreeRTOS.h"
                #include "semphr.h"
#include "FreeRTOS.h"
                #include "semphr.h"
#include "r_ioport.h"
#include "bsp_pin_cfg.h"
FSP_HEADER
#define IOPORT_CFG_NAME g_bsp_pin_cfg
#define IOPORT_CFG_OPEN R_IOPORT_Open
#define IOPORT_CFG_CTRL g_ioport_ctrl

/* IOPORT Instance */
extern const ioport_instance_t g_ioport;

/* IOPORT control structure. */
extern ioport_instance_ctrl_t g_ioport_ctrl;
extern SemaphoreHandle_t uart7rxc;
extern SemaphoreHandle_t uart7txc;
extern SemaphoreHandle_t uart9rxc;
extern SemaphoreHandle_t uart9txc;
extern SemaphoreHandle_t uart8txc;
extern SemaphoreHandle_t uart8rxc;
extern SemaphoreHandle_t uart4rxc;
extern SemaphoreHandle_t uart5rxc;
extern SemaphoreHandle_t on8266;
extern SemaphoreHandle_t on_hmi;
void g_common_init(void);
FSP_FOOTER
#endif /* COMMON_DATA_H_ */

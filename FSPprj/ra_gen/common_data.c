/* generated common source file - do not edit */
#include "common_data.h"
ioport_instance_ctrl_t g_ioport_ctrl;
const ioport_instance_t g_ioport =
        {
            .p_api = &g_ioport_on_ioport,
            .p_ctrl = &g_ioport_ctrl,
            .p_cfg = &g_bsp_pin_cfg,
        };
SemaphoreHandle_t uart7rxc;
                #if 1
                StaticSemaphore_t uart7rxc_memory;
                #endif
                void rtos_startup_err_callback(void * p_instance, void * p_data);
SemaphoreHandle_t uart7txc;
                #if 1
                StaticSemaphore_t uart7txc_memory;
                #endif
                void rtos_startup_err_callback(void * p_instance, void * p_data);
SemaphoreHandle_t uart9rxc;
                #if 1
                StaticSemaphore_t uart9rxc_memory;
                #endif
                void rtos_startup_err_callback(void * p_instance, void * p_data);
SemaphoreHandle_t uart9txc;
                #if 1
                StaticSemaphore_t uart9txc_memory;
                #endif
                void rtos_startup_err_callback(void * p_instance, void * p_data);
SemaphoreHandle_t uart8txc;
                #if 1
                StaticSemaphore_t uart8txc_memory;
                #endif
                void rtos_startup_err_callback(void * p_instance, void * p_data);
SemaphoreHandle_t uart8rxc;
                #if 1
                StaticSemaphore_t uart8rxc_memory;
                #endif
                void rtos_startup_err_callback(void * p_instance, void * p_data);
SemaphoreHandle_t uart4rxc;
                #if 1
                StaticSemaphore_t uart4rxc_memory;
                #endif
                void rtos_startup_err_callback(void * p_instance, void * p_data);
SemaphoreHandle_t uart5rxc;
                #if 1
                StaticSemaphore_t uart5rxc_memory;
                #endif
                void rtos_startup_err_callback(void * p_instance, void * p_data);
SemaphoreHandle_t on_hmi;
                #if 1
                StaticSemaphore_t on_hmi_memory;
                #endif
                void rtos_startup_err_callback(void * p_instance, void * p_data);
SemaphoreHandle_t on8266;
                #if 1
                StaticSemaphore_t on8266_memory;
                #endif
                void rtos_startup_err_callback(void * p_instance, void * p_data);
void g_common_init(void) {
uart7rxc =
                #if 1
                xSemaphoreCreateBinaryStatic(&uart7rxc_memory);
                #else
                xSemaphoreCreateBinary();
                #endif
                if (NULL == uart7rxc) {
                rtos_startup_err_callback(uart7rxc, 0);
                }
uart7txc =
                #if 1
                xSemaphoreCreateBinaryStatic(&uart7txc_memory);
                #else
                xSemaphoreCreateBinary();
                #endif
                if (NULL == uart7txc) {
                rtos_startup_err_callback(uart7txc, 0);
                }
uart9rxc =
                #if 1
                xSemaphoreCreateBinaryStatic(&uart9rxc_memory);
                #else
                xSemaphoreCreateBinary();
                #endif
                if (NULL == uart9rxc) {
                rtos_startup_err_callback(uart9rxc, 0);
                }
uart9txc =
                #if 1
                xSemaphoreCreateBinaryStatic(&uart9txc_memory);
                #else
                xSemaphoreCreateBinary();
                #endif
                if (NULL == uart9txc) {
                rtos_startup_err_callback(uart9txc, 0);
                }
uart8txc =
                #if 1
                xSemaphoreCreateBinaryStatic(&uart8txc_memory);
                #else
                xSemaphoreCreateBinary();
                #endif
                if (NULL == uart8txc) {
                rtos_startup_err_callback(uart8txc, 0);
                }
uart8rxc =
                #if 1
                xSemaphoreCreateBinaryStatic(&uart8rxc_memory);
                #else
                xSemaphoreCreateBinary();
                #endif
                if (NULL == uart8rxc) {
                rtos_startup_err_callback(uart8rxc, 0);
                }
uart4rxc =
                #if 1
                xSemaphoreCreateBinaryStatic(&uart4rxc_memory);
                #else
                xSemaphoreCreateBinary();
                #endif
                if (NULL == uart4rxc) {
                rtos_startup_err_callback(uart4rxc, 0);
                }
uart5rxc =
                #if 1
                xSemaphoreCreateBinaryStatic(&uart5rxc_memory);
                #else
                xSemaphoreCreateBinary();
                #endif
                if (NULL == uart5rxc) {
                rtos_startup_err_callback(uart5rxc, 0);
                }
on_hmi =
                #if 0
                #if 1
                xSemaphoreCreateRecursiveMutexStatic(&on_hmi_memory);
                #else
                xSemaphoreCreateRecursiveMutex();
                #endif
                #else
                #if 1
                xSemaphoreCreateMutexStatic(&on_hmi_memory);
                #else
                xSemaphoreCreateMutex();
                #endif
                #endif
                if (NULL == on_hmi) {
                rtos_startup_err_callback(on_hmi, 0);
                }
on8266 =
                #if 0
                #if 1
                xSemaphoreCreateRecursiveMutexStatic(&on8266_memory);
                #else
                xSemaphoreCreateRecursiveMutex();
                #endif
                #else
                #if 1
                xSemaphoreCreateMutexStatic(&on8266_memory);
                #else
                xSemaphoreCreateMutex();
                #endif
                #endif
                if (NULL == on8266) {
                rtos_startup_err_callback(on8266, 0);
                }
}

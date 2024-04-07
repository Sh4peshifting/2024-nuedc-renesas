#ifndef __FIRE_ALARM_H__
#define __FIRE_ALARM_H__

#include "hal_data.h"

#define FIRE_ALARM_Pin (BSP_IO_PORT_06_PIN_10)
#define FIRE_DETECTED_Pin_LEVEL BSP_IO_LEVEL_LOW

typedef enum
{
    FIRE_NOT_DETECTED = 0,
    FIRE_DETECTED = 1
} fire_status_t;

fire_status_t fire_detect(void);

#endif

#include "fire_alarm.h"

fire_status_t fire_detect(void)
{
  bsp_io_level_t level;
  R_IOPORT_PinRead(&g_ioport_ctrl, FIRE_ALARM_Pin, &level);

  if (level == FIRE_DETECTED_Pin_LEVEL)
  {
    return FIRE_DETECTED;
  }
  else
  {
    return FIRE_NOT_DETECTED;
  }
}

#ifndef __IC_DETECT_H__
#define __IC_DETECT_H__

#include "hal_data.h"
#include "rc522.h"

void ic_detect_init(void);
uint8_t read_card(uint8_t *read_uid, void (*funCallBack)(void));
uint8_t read_card_pro(uint8_t *read_uid);
#endif

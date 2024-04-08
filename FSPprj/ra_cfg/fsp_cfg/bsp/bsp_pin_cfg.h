/* generated configuration header file - do not edit */
#ifndef BSP_PIN_CFG_H_
#define BSP_PIN_CFG_H_
#include "r_ioport.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#define m_a1 (BSP_IO_PORT_00_PIN_14)
#define step_dir (BSP_IO_PORT_03_PIN_01)
#define led (BSP_IO_PORT_04_PIN_00)
#define m_d1 (BSP_IO_PORT_04_PIN_11)
#define m_c1 (BSP_IO_PORT_05_PIN_05)
#define m_a2 (BSP_IO_PORT_05_PIN_13)
#define firepin (BSP_IO_PORT_06_PIN_10)
#define m_b1 (BSP_IO_PORT_07_PIN_04)
#define m_b2 (BSP_IO_PORT_07_PIN_05)
#define m_d2 (BSP_IO_PORT_07_PIN_08)
#define m_c2 (BSP_IO_PORT_08_PIN_06)
#define track2 (BSP_IO_PORT_09_PIN_01)
extern const ioport_cfg_t g_bsp_pin_cfg; /* R7FA6M5BF2CBG.pincfg */

void BSP_PinConfigSecurityInit();

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif /* BSP_PIN_CFG_H_ */

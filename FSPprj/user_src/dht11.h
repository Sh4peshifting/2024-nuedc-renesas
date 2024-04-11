#ifndef __DHT11_H
#define __DHT11_H

#include "hal_data.h"

#define DHT11_Pin (BSP_IO_PORT_03_PIN_03)

#define SUCCESS 0
#define ERROR 1

#define HIGH 1
#define LOW 0

#define DHT11_Mode_Out_PP() R_IOPORT_PinCfg(&g_ioport_ctrl, DHT11_Pin, IOPORT_CFG_PORT_DIRECTION_OUTPUT)
#define DHT11_Mode_IPU() R_IOPORT_PinCfg(&g_ioport_ctrl, DHT11_Pin, IOPORT_CFG_PORT_DIRECTION_INPUT)

#define Delay_us(x) R_BSP_SoftwareDelay(x, BSP_DELAY_UNITS_MICROSECONDS)
#define Delay_ms(x) R_BSP_SoftwareDelay(x, BSP_DELAY_UNITS_MILLISECONDS)

#define DHT11_DATA_OUT(pin_level)                   \
	if (pin_level)                                  \
		R_IOPORT_PinWrite(&g_ioport_ctrl, DHT11_Pin, BSP_IO_LEVEL_HIGH); \
	else                                    \
		R_IOPORT_PinWrite(&g_ioport_ctrl, DHT11_Pin, BSP_IO_LEVEL_LOW)

#define DHT11_DATA_IN() user_DHT11_PinRead()

typedef struct
{
	uint8_t humi_int;
	uint8_t humi_deci;
	uint8_t temp_int;
	uint8_t temp_deci;
	uint8_t check_sum;

} DHT11_Data_TypeDef;

typedef struct{
	float temp;
	float humi;
}DHT11_Data;
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data);
DHT11_Data read_dht11(void);

#endif

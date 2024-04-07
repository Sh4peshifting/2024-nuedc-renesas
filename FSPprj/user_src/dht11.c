#include "dht11.h"

static bsp_io_level_t user_DHT11_PinRead(void)
{
    bsp_io_level_t level;
    R_IOPORT_PinRead(&g_ioport_ctrl, DHT11_Pin, &level);
    return level;
}

static uint8_t Read_Byte(void)
{
	uint8_t i, temp = 0;

	for (i = 0; i < 8; i++)
	{
		while (DHT11_DATA_IN() == BSP_IO_LEVEL_LOW)
			;

		Delay_us(40);

		if (DHT11_DATA_IN() == BSP_IO_LEVEL_HIGH)
		{
			while (DHT11_DATA_IN() == BSP_IO_LEVEL_HIGH)
				;

			temp |= (uint8_t)(0x01 << (7 - i));
		}
		else
		{
			temp &= (uint8_t) ~(0x01 << (7 - i));
		}
	}
	return temp;
}

uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data)
{
	DHT11_Mode_Out_PP();
	DHT11_DATA_OUT(LOW);
	Delay_ms(18);

	DHT11_DATA_OUT(HIGH);

	Delay_us(30);

	DHT11_Mode_IPU();

	if (DHT11_DATA_IN() == BSP_IO_LEVEL_LOW)
	{
		while (DHT11_DATA_IN() == BSP_IO_LEVEL_LOW)
			;

		while (DHT11_DATA_IN() == BSP_IO_LEVEL_HIGH)
			;

		DHT11_Data->humi_int = Read_Byte();

		DHT11_Data->humi_deci = Read_Byte();

		DHT11_Data->temp_int = Read_Byte();

		DHT11_Data->temp_deci = Read_Byte();

		DHT11_Data->check_sum = Read_Byte();

		DHT11_Mode_Out_PP();
		DHT11_DATA_OUT(HIGH);

		if (DHT11_Data->check_sum == DHT11_Data->humi_int + DHT11_Data->humi_deci +
										 DHT11_Data->temp_int + DHT11_Data->temp_deci)
			return SUCCESS;
		else
			return ERROR;
	}
	else
	{
		return ERROR;
	}
}


DHT11_Data read_dht11(void)
{
	DHT11_Data_TypeDef dht11_data;
	DHT11_Data dht11;
	Read_DHT11(&dht11_data);
	dht11.humi=dht11_data.humi_int;
	dht11.temp=dht11_data.temp_int;
	return dht11;
}


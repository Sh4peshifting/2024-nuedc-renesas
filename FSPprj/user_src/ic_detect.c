#include "ic_detect.h"

static void PCD_init(void)
{

	RS522_RST(1);
	vTaskDelay(2);
	RS522_RST(0);
	vTaskDelay(2);
	RS522_RST(1);
	vTaskDelay(2);

	MFRC_WriteReg(MFRC_CommandReg, MFRC_RESETPHASE);
	vTaskDelay(2);

	MFRC_WriteReg(MFRC_ModeReg, 0x3D);
	MFRC_WriteReg(MFRC_TReloadRegL, 30);
	MFRC_WriteReg(MFRC_TReloadRegH, 0);
	MFRC_WriteReg(MFRC_TModeReg, 0x8D);
	MFRC_WriteReg(MFRC_TPrescalerReg, 0x3E);
	MFRC_WriteReg(MFRC_TxAutoReg, 0x40);

	PCD_AntennaOff();
	vTaskDelay(2);
	PCD_AntennaOn();
}

void ic_detect_init(void)
{
	R_SPI_Open(&SPI_CTRL_HANDLER, &SPI_CFG_HANDLER);
	MFRC_Init();
	PCD_init();
}

uint8_t read_card(uint8_t *read_uid, void (*funCallBack)(void))
{
	uint8_t temp[5];
	if (PCD_Request(0x52, temp) == 0)
	{
		if (PCD_Anticoll(read_uid) == 0)
		{
			if (funCallBack != NULL)
				funCallBack();
			return 0;
		}
	}
	return 1;
}


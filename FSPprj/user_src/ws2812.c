/************************************************************
 * @FileName:     	ws2812.c
 * @Author:				Hermes
 * @Version:
 * @Date:
 * @Description:  SPI ��ʽʵ�ֹ����뷢�� �ƴ�����ģ��
 *************************************************************/
#include "ws2812.h"

uint8_t ws2812_data_buffer[WS2812_LED_NUM][24];

RGB_Color rgb_color;
HSV_Color hsv_color;


static volatile bool g_sci_transfer_complete = false;
void sci_spi_callback (spi_callback_args_t * p_args)
{
    if (SPI_EVENT_TRANSFER_COMPLETE == p_args->event)
    {
        g_sci_transfer_complete = true;
    }
}

static void user_sci_spi_write(uint8_t * p_data, uint32_t length)
{
	g_sci_transfer_complete = false;
	R_SCI_SPI_Write(SCI_SPI_HANDLER, p_data, length, SPI_BIT_WIDTH_8_BITS);
	while (!g_sci_transfer_complete)
	{
	}
}


/**
 * @Description  	WS2812�ƴ���ʼ����������
 * @Param     	  {void}
 * @Return    	  {void}
 */
void ws2812_Init(void)
{

	R_SCI_SPI_Open(g_sci_spi3.p_ctrl,g_sci_spi3.p_cfg);
	uint16_t i;
	uint8_t j;

	for (i = 0; i < WS2812_LED_NUM; i++)
	{
		for (j = 0; j < 24; j++)
		{
			ws2812_data_buffer[i][j] = SIG_0;
			if(i+j==0) ws2812_data_buffer[i][j] = 0x80;//fix bug

		}
	}
	ws2812_Send_Data();
	R_BSP_SoftwareDelay(WS2812_LED_NUM * 10, BSP_DELAY_UNITS_MILLISECONDS);
	//vTaskDelay(WS2812_LED_NUM * 10);
}

/**
 * @Description  	WS2812 ��������
 * @Param     	  {void}
 * @Return    	  {void}
 */
void ws2812_Send_Data(void)
{
	user_sci_spi_write((uint8_t *)ws2812_data_buffer, WS2812_LED_NUM * 24);
}

// ����ԭɫ�������ݺϲ�Ϊ24λ����
uint32_t ws281x_color(uint8_t red, uint8_t green, uint8_t blue)
{
	return green << 16 | red << 8 | blue;
}

/**
 * @Description  	WS2812 ���õ�n���������ɫ
 * @Param     n:�ڼ�������   red:0-255   green:0-255    blue:0-255 	   eg:yellow:255 255 0
 * @Return
 */

// �趨��n���������ɫ
void ws281x_setPixelRGB(uint16_t n, uint8_t red, uint8_t green, uint8_t blue)
{
	uint8_t i;

	if (n < WS2812_LED_NUM)
	{
		for (i = 0; i < 24; ++i)
		{
			ws2812_data_buffer[n][i] = (((ws281x_color(red, green, blue) << i) & 0X800000) ? SIG_1 : SIG_0);
		}
	}
	ws2812_Send_Data();
	osDelay(10);
}

/**
 * @Description  	WS2812 ���õ�����ɫ���̶��ģ�
 * @Param       		 n:�ڼ�������   color:������ɫ��0-7��
 * @Return
 */
void set_pixel_rgb(uint16_t n, uint8_t color)
{
	switch (color)
	{
	case Red:
		ws281x_setPixelRGB(n, 255, 0, 0);
		break;
	case Green:
		ws281x_setPixelRGB(n, 0, 255, 0);
		break;
	case Blue:
		ws281x_setPixelRGB(n, 0, 0, 255);
		break;
	case Yellow:
		ws281x_setPixelRGB(n, 255, 255, 0);
		break;
	case Purple:
		ws281x_setPixelRGB(n, 255, 0, 255);
		break;
	case Orange:
		ws281x_setPixelRGB(n, 255, 125, 0);
		break;
	case Indigo:
		ws281x_setPixelRGB(n, 0, 255, 255);
		break;
	case White:
		ws281x_setPixelRGB(n, 255, 255, 255);
		break;
	}
}

// ���ùرյ�n������
void ws281x_ShutoffPixel(uint16_t n)
{
	uint8_t i;

	if (n < WS2812_LED_NUM)
	{
		for (i = 0; i < 24; ++i)
		{
			ws2812_data_buffer[n][i] = SIG_0;
			if(n+i==0) ws2812_data_buffer[n][i] = 0x80;//fix bug
		}
	}
	ws2812_Send_Data();
	osDelay(10);
}

/**
 * @Description  	WS2812�ر����еƹ�		1. ����WS2812_LED_NUM * 24λ�� 0 ��

 * @Param     	  {void}
 * @Return    	  {void}
*/
void ws2812_AllShutOff(void)
{
	uint16_t i;
	uint8_t j;

	for (i = 0; i < WS2812_LED_NUM; i++)
	{
		for (j = 0; j < 24; j++)
		{
			ws2812_data_buffer[i][j] = SIG_0;
			if(i+j==0)
			{
				ws2812_data_buffer[i][j] = 0x80;//fix bug
			}
		}
	}
	ws2812_Send_Data();
	osDelay(10 * WS2812_LED_NUM);
}

void ws2812_all_on(float brightness, uint32_t GRB_color)
{
	rgb_color.G = (unsigned char)GRB_color >> 16;
	rgb_color.R = (unsigned char)GRB_color >> 8;
	rgb_color.B = (unsigned char)GRB_color;
	
	__brightnessAdjust(brightness / 100.0f, rgb_color);
	for (uint16_t j = 0; j < WS2812_LED_NUM; j++)
	{
		ws2812_Set_one_LED_Color(j, (rgb_color.G << 16) | (rgb_color.R << 8) | (rgb_color.B));
	}
		ws2812_Send_Data();
}


/**
 * @Description  	WS2812����ĳһλ��LED����ɫ ��������
 * @Param     	  {uint16_t LED_index ,uint32_t GRB_color}
 * @Return    	  {void}
 */
void ws2812_Set_one_LED_Color(uint16_t LED_index, uint32_t GRB_color)
{
	uint8_t i = 0;
	uint32_t cnt = 0x800000;
	if (LED_index < WS2812_LED_NUM)
	{
		for (i = 0; i < 24; ++i)
		{
			if (GRB_color & cnt)
			{
				ws2812_data_buffer[LED_index][i] = SIG_1;
			}
			else
			{
				ws2812_data_buffer[LED_index][i] = SIG_0;
				if(i+LED_index==0) ws2812_data_buffer[LED_index][i] = 0x80;//fix bug
			}
			cnt >>= 1;
		}
	}
}

void light_ctrl(uint8_t switch_flag)
{
	if (switch_flag == LIGHT_ON)
	{
		ws2812_all_on(20, C_Red);
	}
	else
	{
		ws2812_AllShutOff();
	}
}


/***********************************************************
										Private Function
************************************************************/
/**
 * @Description  	����������ֵ
 * @Param     	  {float a,float b}
 * @Return    	  {float}
 */
float __getMaxValue(float a, float b)
{
	return a >= b ? a : b;
}

/**
 * @Description  	���������Сֵ
 * @Param     	  {void}
 * @Return    	  {void}
 */
float __getMinValue(float a, float b)
{
	return a <= b ? a : b;
}

/**
 * @Description  	RGB תΪ HSV
 * @Param     	  {RGB_Color RGB, HSV_Color *HSV}
 * @Return    	  {void}
 */
void __RGB_2_HSV(RGB_Color RGB, HSV_Color *HSV)
{
	float r, g, b, minRGB, maxRGB, deltaRGB;

	r = RGB.R / 255.0f;
	g = RGB.G / 255.0f;
	b = RGB.B / 255.0f;
	maxRGB = __getMaxValue(r, __getMaxValue(g, b));
	minRGB = __getMinValue(r, __getMinValue(g, b));
	deltaRGB = maxRGB - minRGB;

	HSV->V = deltaRGB;
	if (maxRGB != 0.0f)
	{
		HSV->S = deltaRGB / maxRGB;
	}
	else
	{
		HSV->S = 0.0f;
	}
	if (HSV->S <= 0.0f)
	{
		HSV->H = 0.0f;
	}
	else
	{
		if (r == maxRGB)
		{
			HSV->H = (g - b) / deltaRGB;
		}
		else
		{
			if (g == maxRGB)
			{
				HSV->H = 2.0f + (b - r) / deltaRGB;
			}
			else
			{
				if (b == maxRGB)
				{
					HSV->H = 4.0f + (r - g) / deltaRGB;
				}
			}
		}
		HSV->H = HSV->H * 60.0f;
		if (HSV->H < 0.0f)
		{
			HSV->H += 360;
		}
		HSV->H /= 360;
	}
}

/**
 * @Description  	HSV תΪ RGB
 * @Param     	  {void}
 * @Return    	  {void}
 */
void __HSV_2_RGB(HSV_Color HSV, RGB_Color *RGB)
{
	float R, G, B, aa, bb, cc, f;
	int k;
	if (HSV.S <= 0.0f)
		R = G = B = HSV.V;
	else
	{
		if (HSV.H == 1.0f)
		{
			HSV.H = 0.0f;
		}
		HSV.H *= 6.0f;
		k = (int)floor(HSV.H);
		f = HSV.H - k;
		aa = HSV.V * (1.0f - HSV.S);
		bb = HSV.V * (1.0f - HSV.S * f);
		cc = HSV.V * (1.0f - (HSV.S * (1.0f - f)));
		switch (k)
		{
		case 0:
			R = HSV.V;
			G = cc;
			B = aa;
			break;
		case 1:
			R = bb;
			G = HSV.V;
			B = aa;
			break;
		case 2:
			R = aa;
			G = HSV.V;
			B = cc;
			break;
		case 3:
			R = aa;
			G = bb;
			B = HSV.V;
			break;
		case 4:
			R = cc;
			G = aa;
			B = HSV.V;
			break;
		case 5:
			R = HSV.V;
			G = aa;
			B = bb;
			break;
		}
	}
	RGB->R = (unsigned char)(R * 255);
	RGB->G = (unsigned char)(G * 255);
	RGB->B = (unsigned char)(B * 255);
}

/**
 * @Description  	���ȵ���
 * @Param     	  {void}
 * @Return    	  {void}
 */
void __brightnessAdjust(float percent, RGB_Color RGB)
{
	if (percent < 0.01f)
	{
		percent = 0.01f;
	}
	if (percent > 1.0f)
	{
		percent = 1.0f;
	}
	__RGB_2_HSV(RGB, &hsv_color);
	hsv_color.V = percent;
	__HSV_2_RGB(hsv_color, &rgb_color);
}
/************************************************************
														EOF
*************************************************************/

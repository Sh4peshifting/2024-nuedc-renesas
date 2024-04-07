
#ifndef __WS2812_H
#define __WS2812_H

#include "hal_data.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define osDelay(milisec) vTaskDelay(milisec);
#define SCI_SPI_HANDLER g_sci_spi3.p_ctrl

#define LIGHT_ON 1
#define LIGHT_OFF 0


#define WS2812_LED_NUM 	8

// 11111000  SIG_1   5/8 = 62.5%
// 11100000  SIG_0   3/8 = 37.5%

#define 		SIG_1 		0XF8
#define 		SIG_0  		0XE0


#define	C_Red		0x00FF00
#define	C_Green		0xFF0000
#define	C_Blue		0x0000FF
#define	C_Yellow   	0xFFFF00
#define	C_Purple	0x00FFFF
#define	C_Orange	0x7DFF00
#define	C_indigo	0xFF00FF
#define	C_white 	0xFFFFFF

enum Color
{
	Red,
	Green,
	Blue,
	Yellow,
	Purple,
	Orange,
	Indigo,
	White,
};

typedef struct RGB_Color{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char l;
}RGB_Color;

typedef struct HSV_Color{
	float H;
	float S;
	float V;
}HSV_Color;

void ws2812_Init(void);
void ws2812_Send_Data(void);
void ws2812_AllShutOff(void);

void ws2812_Set_one_LED_Color(uint16_t LED_index ,uint32_t GRB_color);
void ws281x_setPixelRGB(uint16_t n ,uint8_t red, uint8_t green, uint8_t blue);
void ws281x_ShutoffPixel(uint16_t n);
void set_pixel_rgb(uint16_t n,uint8_t color);

void light_ctrl(uint8_t switch_flag);

/************************************************************
											Peivate Function
************************************************************/
void __brightnessAdjust(float percent, RGB_Color RGB);

#endif

/************************************************************
														EOF
*************************************************************/


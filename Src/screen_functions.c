/**
 ******************************************************************************
 * @file           : screen_functions.c
 * @brief          : Screen output functions
 * Created on: Sep 22, 2018
 * Author: tapio
 ******************************************************************************
 */

#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "main.h"
#include "screen_functions.h"

#include "stm32f7xx_hal.h"

#include "stm32746g_discovery.h"
#include "stm32746g_discovery_lcd.h"

// Screen initialization
void initscreen(uint32_t BackGroundColor, uint32_t ForeGroundColor) {

	// Start LCD
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
	BSP_LCD_SelectLayer(0);
	BSP_LCD_DisplayOn();
	BSP_LCD_Clear(BackGroundColor);
	BSP_LCD_SetBackColor(BackGroundColor);
	BSP_LCD_SetTextColor(ForeGroundColor);
	BSP_LCD_SetFont(&Font24);
}

void LCDwrite(char str[]) {

	static uint32_t line = 0;

	char intstr[50];

	BSP_LCD_ClearStringLine(line);
	BSP_LCD_DisplayStringAtLine((uint16_t) line, (uint8_t *) " ");
	BSP_LCD_DisplayStringAt(0, LINE(line), (uint8_t *) " ", LEFT_MODE);
	snprintf(intstr, 50, str);
	BSP_LCD_DisplayStringAtLine((uint16_t) line, (uint8_t *) intstr);
	BSP_LCD_DisplayStringAt(0, LINE(line), (uint8_t *) intstr, LEFT_MODE);
	line++;
	if (line > 10) {
		BSP_LCD_Clear(BackGColor);
		line = 0;
	}
}

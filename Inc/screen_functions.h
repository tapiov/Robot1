/*
 * screen_functions.h
 *
 *  Created on: Sep 22, 2018
 *      Author: tapio
 */

#ifndef SCREEN_FUNCTIONS_H_
#define SCREEN_FUNCTIONS_H_

#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "main.h"

#include "stm32746g_discovery_lcd.h"

#define BackGColor LCD_COLOR_BLACK
#define ForeGColor LCD_COLOR_YELLOW

extern void initscreen(uint32_t BGColor, uint32_t FGColor);
extern void LCDwrite(char str[]);

#endif /* SCREEN_FUNCTIONS_H_ */

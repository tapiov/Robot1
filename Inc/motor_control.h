/*
 * motor_control.h
 *
 *  Created on: Sep 21, 2018
 *  Author: tapio
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include "stdbool.h"

ADC_HandleTypeDef hadc3;

DMA2D_HandleTypeDef hdma2d;

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c3;

LTDC_HandleTypeDef hltdc;

RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim8;
TIM_HandleTypeDef htim12;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart6;

SDRAM_HandleTypeDef hsdram1;

extern void Master_Write(uint8_t sadd, uint8_t byte);

extern void motor_write(uint8_t motor, bool direction, uint16_t speed);

extern void move(bool direction, uint16_t speed);

extern void turn(bool direction, uint16_t speed);

extern void initscreen(uint32_t BackGroundColor, uint32_t ForeGroundColor);

extern void LCDwrite(char str[]);

#endif /* MOTOR_CONTROL_H_ */

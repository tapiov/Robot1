/**
 ******************************************************************************
 * @file           : motor_control.c
 * @brief          : Motor control functions
 * Created on: Sep 21, 2018
 * Author: tapio
 ******************************************************************************
 */

#include "main.h"
#include "stm32f7xx_hal.h"

#include "stdbool.h"

#include "motor_control.h"

void Master_Write(uint8_t sadd, uint8_t byte) {

	uint8_t addr_PCA9685 = 0x60;
	uint8_t buffer[5];

	buffer[0] = 0;
	buffer[1] = 0;
	buffer[2] = 0;
	buffer[3] = 0;
	buffer[4] = 0;

	buffer[0] = sadd;
	buffer[1] = byte;

	HAL_I2C_Master_Transmit(&hi2c1, addr_PCA9685 << 1, buffer, 2, 100);
}

void motor_write(uint8_t motor, bool direction, uint16_t speed) {

	uint16_t scaled_speed;
	uint8_t subadd_in1, subadd_in2, subadd_pwm;
	uint8_t scaled_lsb, scaled_msb;

	if (speed == 0) {
		// This is stop
		scaled_speed = 0;
	} else {
		// Scale and zero 4 MSB
		scaled_speed = ((int) ((((float) speed) / 100.0) * 4096)) & 0x0FFF;
	}

	scaled_lsb = scaled_speed & 0x00FF;
	scaled_msb = scaled_speed >> 8;

	switch (motor) {

	case 1:
		subadd_in1 = 0x2E;
		subadd_in2 = 0x2A;
		subadd_pwm = 0x26;
		break;

	case 2:
		subadd_in1 = 0x32;
		subadd_in2 = 0x36;
		subadd_pwm = 0x3A;
		break;

	case 3:
		subadd_in1 = 0x16;
		subadd_in2 = 0x12;
		subadd_pwm = 0x0E;
		break;

	case 4:
		subadd_in1 = 0x1A;
		subadd_in2 = 0x1E;
		subadd_pwm = 0x22;
		break;

	default:
		subadd_in1 = 0x2E;
		subadd_in2 = 0x2A;
		subadd_pwm = 0x26;
	}

	if (direction) {

		// Forward
		// IN1 = H
		Master_Write(subadd_in1 + 0, 0x00);
		Master_Write(subadd_in1 + 1, 0x10);
		Master_Write(subadd_in1 + 2, 0x00);
		Master_Write(subadd_in1 + 3, 0x00);

		// IN2 = L
		Master_Write(subadd_in2 + 0, 0x00);
		Master_Write(subadd_in2 + 1, 0x00);
		Master_Write(subadd_in2 + 2, 0x00);
		Master_Write(subadd_in2 + 3, 0x10);

		// PWM = scaled_speed
		Master_Write(subadd_pwm + 0, 0x00);
		Master_Write(subadd_pwm + 1, 0x00);
		Master_Write(subadd_pwm + 2, scaled_lsb);
		Master_Write(subadd_pwm + 3, scaled_msb);
	} else {
		// Backward
		// IN1 = L
		Master_Write(subadd_in1 + 0, 0x00);
		Master_Write(subadd_in1 + 1, 0x00);
		Master_Write(subadd_in1 + 2, 0x00);
		Master_Write(subadd_in1 + 3, 0x10);

		// IN2 = H
		Master_Write(subadd_in2 + 0, 0x00);
		Master_Write(subadd_in2 + 1, 0x10);
		Master_Write(subadd_in2 + 2, 0x00);
		Master_Write(subadd_in2 + 3, 0x00);

		// PWM = scaled_speed
		Master_Write(subadd_pwm + 0, 0x00);
		Master_Write(subadd_pwm + 1, 0x00);
		Master_Write(subadd_pwm + 2, scaled_lsb);
		Master_Write(subadd_pwm + 3, scaled_msb);
	}

}

void move(bool direction, uint16_t speed) {

	motor_write(1, direction, speed);
	motor_write(2, direction, speed);
	motor_write(3, direction, speed);
	motor_write(4, direction, speed);

}

void turn(bool direction, uint16_t speed) {

	if (direction) {
		motor_write(1, true, speed);
		motor_write(2, false, speed);
		motor_write(4, true, speed);
		motor_write(3, false, speed);
	} else {
		motor_write(1, false, speed);
		motor_write(2, true, speed);
		motor_write(4, false, speed);
		motor_write(3, true, speed);
	}

}


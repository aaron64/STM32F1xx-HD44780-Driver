/*
 * stm32f1xx_HD44780_ex.c
 *
 *  Created on: Oct 9, 2020
 *      Author: aaronchambers
 */
#include "stm32f1xx_HD44780_ex.h"

void HD44780_SetData(HD44780_TypeDef *HD44780, uint8_t Data)
{
	HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinD0, (Data & 1 << 0));
	HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinD1, (Data & 1 << 1));
	HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinD2, (Data & 1 << 2));
	HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinD3, (Data & 1 << 3));
	HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinD4, (Data & 1 << 4));
	HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinD5, (Data & 1 << 5));
	HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinD6, (Data & 1 << 6));
	HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinD7, (Data & 1 << 7));
}

void HD44780_Send(HD44780_TypeDef *HD44780)
{
	HAL_Delay(HD44780_SPEED);
	HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinEN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinEN, GPIO_PIN_RESET);
}

void HD44780_SendData(HD44780_TypeDef *HD44780, uint8_t Data)
{
	HD44780_SetData(HD44780, Data);
	HD44780_Send(HD44780);
}

uint8_t HD44780_PosOffscreen(uint16_t Pos)
{
	return Pos < 0 || (Pos >= 16 && Pos < 64) || Pos >= 90;
}

uint8_t HD44780_CursorOffscreen(HD44780_TypeDef *HD44780)
{
	return HD44780_PosOffscreen(HD44780->Pos);
}

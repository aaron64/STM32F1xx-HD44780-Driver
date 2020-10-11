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

void HD44780_Read(HD44780_TypeDef *HD44780, char *str)
{
	uint16_t pos = HD44780->Pos;
	int8_t direction = HD44780->Direction;

	HD44780_MoveToPos(HD44780, 0);
	HD44780_Direction(HD44780, HD44780_DIRECTION_RIGHT);

	char c = 0;

	HAL_GPIO_WritePin(GPIOA, HD44780->PinD0|HD44780->PinD1|HD44780->PinD2|HD44780->PinD3
							|HD44780->PinD4|HD44780->PinD5|HD44780->PinD6|HD44780->PinD7
							|HD44780->PinRW|HD44780->PinRS|HD44780->PinEN, GPIO_PIN_RESET);
	GPIO_InitTypeDef GPIO_InitStructRead = {
		.Pin = HD44780->PinD0|HD44780->PinD1|HD44780->PinD2|HD44780->PinD3
				|HD44780->PinD4|HD44780->PinD5|HD44780->PinD6|HD44780->PinD7,

		.Mode = GPIO_MODE_INPUT,
		.Pull = GPIO_PULLDOWN,
		.Speed = GPIO_SPEED_FREQ_HIGH
	};

	HAL_GPIO_Init(HD44780->GPIOPort, &GPIO_InitStructRead);

	HD44780_WriteRS(HD44780, HD44780_RS_EN);
	HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinRW, GPIO_PIN_SET);

	for(int i = 0; i < HD44780_SEGMENTS; i++)
	{
		c = 0;
		HAL_Delay(10);
		HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinEN, GPIO_PIN_SET);
		HAL_Delay(10);
		c |= (HAL_GPIO_ReadPin(HD44780->GPIOPort, HD44780->PinD0) << 0);
		c |= (HAL_GPIO_ReadPin(HD44780->GPIOPort, HD44780->PinD1) << 1);
		c |= (HAL_GPIO_ReadPin(HD44780->GPIOPort, HD44780->PinD2) << 2);
		c |= (HAL_GPIO_ReadPin(HD44780->GPIOPort, HD44780->PinD3) << 3);
		c |= (HAL_GPIO_ReadPin(HD44780->GPIOPort, HD44780->PinD4) << 4);
		c |= (HAL_GPIO_ReadPin(HD44780->GPIOPort, HD44780->PinD5) << 5);
		c |= (HAL_GPIO_ReadPin(HD44780->GPIOPort, HD44780->PinD6) << 6);
		c |= (HAL_GPIO_ReadPin(HD44780->GPIOPort, HD44780->PinD7) << 7);
		str[i] = c;
		HAL_Delay(10);
		HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinEN, GPIO_PIN_RESET);
	}

	for(int i = 0; i < (40-HD44780_SEGMENTS); i++)
	{
		HAL_Delay(10);
		HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinEN, GPIO_PIN_SET);
		HAL_Delay(10);
		HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinEN, GPIO_PIN_RESET);
	}

	for(int i = 0; i < HD44780_SEGMENTS; i++)
	{
		c = 0;
		HAL_Delay(10);
		HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinEN, GPIO_PIN_SET);
		HAL_Delay(10);
		c |= (HAL_GPIO_ReadPin(HD44780->GPIOPort, HD44780->PinD0) << 0);
		c |= (HAL_GPIO_ReadPin(HD44780->GPIOPort, HD44780->PinD1) << 1);
		c |= (HAL_GPIO_ReadPin(HD44780->GPIOPort, HD44780->PinD2) << 2);
		c |= (HAL_GPIO_ReadPin(HD44780->GPIOPort, HD44780->PinD3) << 3);
		c |= (HAL_GPIO_ReadPin(HD44780->GPIOPort, HD44780->PinD4) << 4);
		c |= (HAL_GPIO_ReadPin(HD44780->GPIOPort, HD44780->PinD5) << 5);
		c |= (HAL_GPIO_ReadPin(HD44780->GPIOPort, HD44780->PinD6) << 6);
		c |= (HAL_GPIO_ReadPin(HD44780->GPIOPort, HD44780->PinD7) << 7);
		str[HD44780_SEGMENTS+i] = c;
		HAL_Delay(10);
		HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinEN, GPIO_PIN_RESET);
	}

	str[32] = '\0';

	HD44780_WriteRS(HD44780, HD44780_RS_DI);
	HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinRW, GPIO_PIN_RESET);

	GPIO_InitTypeDef GPIO_InitStructWrite = {
		.Pin = HD44780->PinD0|HD44780->PinD1|HD44780->PinD2|HD44780->PinD3
				|HD44780->PinD4|HD44780->PinD5|HD44780->PinD6|HD44780->PinD7,

		.Mode = GPIO_MODE_OUTPUT_PP,
		.Pull = GPIO_NOPULL,
		.Speed = GPIO_SPEED_FREQ_HIGH
	};

	HAL_GPIO_Init(HD44780->GPIOPort, &GPIO_InitStructWrite);

}

void HD44780_WriteRS(HD44780_TypeDef *HD44780, uint8_t State)
{
	HAL_GPIO_WritePin(HD44780->GPIOPort, HD44780->PinRS, State);
}

uint8_t HD44780_PosOffscreen(uint16_t Pos)
{
	return Pos < 0 || (Pos >= HD44780_SEGMENTS && Pos < 64) || Pos >= 90;
}

uint8_t HD44780_CursorOffscreen(HD44780_TypeDef *HD44780)
{
	return HD44780_PosOffscreen(HD44780->Pos);
}

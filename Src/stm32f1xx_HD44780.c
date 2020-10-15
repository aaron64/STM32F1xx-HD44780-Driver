/*
 * stm32f2xx_HD44780.c
 *
 *  Created on: Oct 8, 2020
 *      Author: aaronchambers
 */
#include <stdio.h>
#include <stdarg.h>

#include "stm32f1xx_HD44780.h"
#include "stm32f1xx_HD44780_ex.h"

HD44780_TypeDef HD44780_Create(GPIO_TypeDef *GPIOPort, uint32_t PinD0, uint32_t PinD1, uint32_t PinD2, uint32_t PinD3, uint32_t PinD4, uint32_t PinD5, uint32_t PinD6, uint32_t PinD7, uint32_t ENPin, uint32_t RWPin, uint32_t RSPin)
{
	HD44780_TypeDef HD44780 = {
		.GPIOPort = GPIOPort,

		.PinD0 = PinD0,
		.PinD1 = PinD1,
		.PinD2 = PinD2,
		.PinD3 = PinD3,
		.PinD4 = PinD4,
		.PinD5 = PinD5,
		.PinD6 = PinD6,
		.PinD7 = PinD7,

		.PinEN = ENPin,
		.PinRW = RWPin,
		.PinRS = RSPin,

		.Pos = 0,
		.Direction = 1
	};

	return HD44780;
}

HD44780_TypeDef HD44780_CreateFromBus(GPIO_TypeDef *GPIOPort, uint32_t StartPin, uint32_t ENPin, uint32_t RWPin, uint32_t RSPin)
{
	HD44780_TypeDef HD44780 = {
		.GPIOPort = GPIOPort,

		.PinD0 = (StartPin << 0),
		.PinD1 = (StartPin << 1),
		.PinD2 = (StartPin << 2),
		.PinD3 = (StartPin << 3),
		.PinD4 = (StartPin << 4),
		.PinD5 = (StartPin << 5),
		.PinD6 = (StartPin << 6),
		.PinD7 = (StartPin << 7),

		.PinEN = ENPin,
		.PinRW = RWPin,
		.PinRS = RSPin,

		.Pos = 0
	};

	return HD44780;
}

void HD44780_Init(HD44780_TypeDef *HD44780, uint8_t Options)
{
	GPIO_InitTypeDef GPIO_InitStruct = {
		.Pin = HD44780->PinD0|HD44780->PinD1|HD44780->PinD2|HD44780->PinD3
						|HD44780->PinD4|HD44780->PinD5|HD44780->PinD6|HD44780->PinD7
						|HD44780->PinEN|HD44780->PinRW|HD44780->PinRS,

		.Mode = GPIO_MODE_OUTPUT_PP,
		.Pull = GPIO_NOPULL,
		.Speed = GPIO_SPEED_FREQ_HIGH
	};

	HAL_GPIO_Init(HD44780->GPIOPort, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOA, HD44780->PinD0|HD44780->PinD1|HD44780->PinD2|HD44780->PinD3
						|HD44780->PinD4|HD44780->PinD5|HD44780->PinD6|HD44780->PinD7
						|HD44780->PinRW|HD44780->PinRS|HD44780->PinEN, GPIO_PIN_RESET);

	
	HD44780_SendData(HD44780, HD44780_FUNCTION_INIT | Options);
	HD44780_Clear(HD44780);
	HD44780_DisplayMode(HD44780, HD44780_DISPLAY_ON);
	HD44780_Direction(HD44780, HD44780_DIRECTION_RIGHT);
}

void HD44780_DisplayMode(HD44780_TypeDef *HD44780, uint8_t Options)
{
	HD44780_SendData(HD44780, HD44780_FUNCTION_DISPLAY | Options);
}

void HD44780_Direction(HD44780_TypeDef *HD44780, uint8_t Options)
{
	if(Options & HD44780_DIRECTION_RIGHT)
		HD44780->Direction = 1;
	else
		HD44780->Direction = -1;
	HD44780_SendData(HD44780, HD44780_FUNCTION_ENTRY_MODE | Options);
}

void HD44780_Shift(HD44780_TypeDef *HD44780, uint8_t Options)
{
	// TODO: Add change to pos
	HD44780_SendData(HD44780, HD44780_FUNCTION_SHIFT | Options);
}

void HD44780_PrintChar(HD44780_TypeDef *HD44780, char c)
{
	HAL_Delay(HD44780_SPEED);
	HD44780_WriteRS(HD44780, HD44780_RS_EN);
	HD44780_SendData(HD44780, c);
	HD44780_WriteRS(HD44780, HD44780_RS_DI);

	HD44780->Pos += HD44780->Direction;
	if(HD44780_CursorOffscreen(HD44780))
	{
		HD44780_SwitchLines(HD44780);
	}
}

void HD44780_Printf(HD44780_TypeDef *HD44780, char *s, ...)
{
	va_list ap;
	va_start(ap, s);
	int size = vsnprintf(NULL, 0, s, ap);
	if(size < 0)
		return;
	char buf[size];
	vsnprintf(buf, size+1, s, ap);
	int i = 0;
	while(buf[i] != '\0')
	{
		HD44780_PrintChar(HD44780, buf[i]);
		i++;
	}
}

void HD44780_Clear(HD44780_TypeDef *HD44780)
{
	HD44780->Pos = 0;
	HD44780_SendData(HD44780, HD44780_FUNCTION_CLEAR);
}

void HD44780_CursorRight(HD44780_TypeDef *HD44780)
{
	HD44780_SendData(HD44780, HD44780_FUNCTION_SHIFT | HD44780_DIRECTION_RIGHT);
}

void HD44780_CursorLeft(HD44780_TypeDef *HD44780)
{
	HD44780_SendData(HD44780, HD44780_FUNCTION_SHIFT | HD44780_DIRECTION_LEFT);
}

void HD44780_CursorUp(HD44780_TypeDef *HD44780)
{
	HD44780_CursorDown(HD44780);
}

void HD44780_CursorDown(HD44780_TypeDef *HD44780)
{
	// TODO: Finish cursor down
	uint8_t pos = HD44780->Pos%HD44780_SEGMENTS;
	
}

void HD44780_MoveToPos(HD44780_TypeDef *HD44780, uint8_t Pos)
{
	if(HD44780_PosOffscreen(Pos))
		return;
	HD44780->Pos = Pos;
	HD44780_SendData(HD44780, HD44780_FUNCTION_SET_DDRAM | Pos);
}

void HD44780_MoveToLine(HD44780_TypeDef *HD44780, uint8_t Line)
{
	// TODO: Handle max lines
	HD44780->Pos = Line;
	HD44780_SendData(HD44780, HD44780_FUNCTION_SET_DDRAM | Line);
}

void HD44780_SwitchLines(HD44780_TypeDef *HD44780)
{
	// TODO: Handle max lines
	if(HD44780->Pos < HD44780_LINE_2)
		if(HD44780->Direction == 1)
			HD44780_MoveToLine(HD44780, HD44780_LINE_2);
		else
			HD44780_MoveToPos(HD44780, HD44780_LINE_1 + 15);
	else if(HD44780->Pos == 65535 && HD44780->Direction == -1)
		HD44780_MoveToPos(HD44780, HD44780_LINE_2 + 15);
	else
		HD44780_MoveToLine(HD44780, HD44780_LINE_1);
}

void HD44780_PrintCustomChar(HD44780_TypeDef *HD44780, uint8_t pos)
{
	HD44780_WriteRS(HD44780, HD44780_RS_EN);
	HD44780_SendData(HD44780, pos);
	HD44780_WriteRS(HD44780, HD44780_RS_DI);
}

void HD44780_RegisterCustomChar(HD44780_TypeDef *HD44780, uint8_t pos, uint8_t *data)
{
	pos *= 8;
	uint8_t cursorPos = HD44780->Pos;
	HD44780_SendData(HD44780, HD44780_FUNCTION_SET_CGRAM);
	HD44780_WriteRS(HD44780, HD44780_RS_EN);
	for(int i = 0; i < 8; i++)
	{
		HAL_Delay(HD44780_SPEED);
		HD44780_SendData(HD44780, data[i]);
	}
	HD44780_WriteRS(HD44780, HD44780_RS_DI);
	HD44780_MoveToPos(HD44780, cursorPos);
}
